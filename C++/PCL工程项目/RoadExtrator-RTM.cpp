/* std */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

/* pcl */
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/io/io.h>

namespace LY {

    template<typename PointT>
    class RoadFPExtractor {
    public:
        typedef typename pcl::PCLBase<PointT>::PointCloudPtr PointCloudPtr;
        typedef typename pcl::PCLBase<PointT>::PointCloudConstPtr PointCloudConstPtr;

        /* 构造器
        * \brief 初始化构造器
        * \param minDistance 最终采样点的最小间隔距离
        */
        RoadFPExtractor(const float minDistance = 0.5f)
            : _cloud(new pcl::PointCloud<PointT>) {
            _minDistance = minDistance;
            _mean = 0.0f;
            _variance = 0.0f;
            _deltaZ = 0.0f;
        }

        /* 析构器 */
        ~RoadFPExtractor() {}

        /*
        * \brief 设置最终特点的最小间隔距离
        * \param distance 特征点距离，单位是 米(m)
        */
        void setMinDistanceOfFP(float distance) {
            _minDistance = distance;
        }

        /*
         * \brief 设置Z坐标的最大差距
         **/
        void setDeltaZField(float deltaZ) {
            _deltaZ = deltaZ;
        }

        /*
        * \brief 设置要处理的点云
        * \param another_cloud 另一个点云类型，点云类型必须保持一致
        */
        void setInputCloud(const PointCloudConstPtr &another_cloud) {
            for (auto point : another_cloud->points) {
                std::vector<float> v;
                v.push_back(point.x); v.push_back(point.y); v.push_back(point.z);
                _vecPointCloud.push_back(v);
            }
            _vecPointCloud.shrink_to_fit();
            __sortAndFillCloud();
            _kdtree.setInputCloud(_cloud);
        }

        /* 主要的处理函数
        * \brief 提取特征点
        * \param fp 输出结果到该点云对象
        */
        void filterRoadFuturePoint(PointCloudPtr &fp) {

            /* 1. 获取特征点的大致位置(完全是等间隔的道路点，不考虑任何其他因素) */
            std::vector<int> vecStdIndex;
            __getAppropriateFP(vecStdIndex);

            /* 2. 大致确定各类型特征点 */
            bool next_is_EdgePoint = false; /* 加快搜索 */
            std::vector<int> vecCoarseIndex;
            for (int i = 0; i < _cloud->points.size(); ++i) {
                auto it = std::find(std::begin(vecStdIndex), std::end(vecStdIndex), i);
                if (it != std::end(vecStdIndex))
                    continue;
                RFPT type = __isFP(_cloud->points[i], i, next_is_EdgePoint);
                switch (type) {
                case EdgePoint:
                    vecCoarseIndex.push_back(i); break;
                case RightAnglePoint:
                    vecCoarseIndex.push_back(i); break;
                case ExtremePoint:
                    vecCoarseIndex.push_back(i); break;
                case InflectionPoint:
                    vecCoarseIndex.push_back(i); break;
                case NormalPoint:
                    break;
                }
                if (next_is_EdgePoint) {
                    vecCoarseIndex.push_back(++i);
                    next_is_EdgePoint = false;
                }
            }

            /* 3. 重采样(精细化)道路特征点 */
            std::vector<int> vecInerIndex;
            int coarse_index_from = 0; /* vecCoarseIndex 的索引，不是真实索引 */
            for (size_t i = 0; i < vecStdIndex.size() - 1; ++i) {
                __calcInnerIndexOf2Points(_cloud->points[vecStdIndex[i]], _cloud->points[vecStdIndex[i + 1]], vecCoarseIndex, coarse_index_from, vecInerIndex);
            }

            /* 4. 合并索引，排序索引，去重索引 */
            _vecFPIndex.insert(_vecFPIndex.end(), vecStdIndex.begin(), vecStdIndex.end());
            _vecFPIndex.insert(_vecFPIndex.end(), vecInerIndex.begin(), vecInerIndex.end());
            struct {
                bool operator()(int v1, int v2) {
                    return v1 < v2;
                }
            } customeIndexLess;
            std::sort(_vecFPIndex.begin(), _vecFPIndex.end(), customeIndexLess);
            std::vector<int>::iterator it = std::unique(_vecFPIndex.begin(), _vecFPIndex.end());
            _vecFPIndex.erase(it, _vecFPIndex.end());

            /* 5. 优化结果 */
            __optimizeFP(vecInerIndex);

            /* 6. 保存结果 */
            for (auto v : _vecFPIndex) {
                fp->points.push_back(_cloud->points[v]);
            }

        }

    private:
        PointCloudPtr _cloud; /* 原始点云 */
        std::vector<std::vector<float>> _vecPointCloud; /* 存储原始点云的索引 */
        std::vector<int> _vecFPIndex; /* 特征点索引 */
        float _minDistance;  /* 特征点之间最短距离(点云已排序) */
        float _deltaZ; /* 设置 Z 方向的最大高差 */
        float _mean, _variance; /* 原始点云点距离的均值和方差(点云已排序) */
        typedef enum RoadFeaturePointType {
            EdgePoint, RightAnglePoint, ExtremePoint, InflectionPoint, NormalPoint /* 道路特征点类型 */
        } RFPT;
        pcl::KdTreeFLANN<PointT> _kdtree; /* Kd 搜索树 */

        /*
        * \brief 对点云索引 _vecPointCloud 从小到大排序
        */
        void __sortAndFillCloud() {
            struct {
                bool operator()(std::vector<float> v1, std::vector<float> v2) {
                    return v1[0] < v2[0];
                }
            } customeCoordiateLess;

            std::sort(_vecPointCloud.begin(), _vecPointCloud.end(), customeCoordiateLess);
            for (auto v : _vecPointCloud) {
                PointT point;
                point.x = v[0]; point.y = v[1]; point.z = v[2];
                _cloud->points.push_back(point);
            }
            __calcGlobalAverageDistance(_mean, _variance);
        }

        /*
        * \brief 计算两个法向量的夹角
        * \param x1
        * \param y1
        * \param z1
        * \param x2
        * \param y2
        * \param z2
        */
        inline float
        __calcAngleOf2Vectors(float x1, float y1, float z1, float x2, float y2, float z2) {
            float dot = x1 * x2 + y1 * y2 + z1 * z2;
            float square = std::sqrt(x1 * x1 + y1 * y1 + z1 * z1) * std::sqrt(x2 * x2 + y2 * y2 + z2 * z2);
            return (dot / square);
        }

        /*
        * \brief 计算均值和方差(在已排序的点云上进行操作)
        * \param Mean 均值
        * \param Variance 方差
        */
        void __calcGlobalAverageDistance(float &Mean, float &Variance) {

            /* 计算距离和 */
            std::vector<float> vecDistance;
            for (size_t i = 0; i < _cloud->points.size() - 1; i++)
                vecDistance.push_back(__calcDistanceOf2Points(_cloud->points[i], _cloud->points[i + 1]));
            vecDistance.shrink_to_fit();

            /* 计算均值 */
            Mean = std::accumulate(vecDistance.begin(), vecDistance.end(), 0.0f) / vecDistance.size();

            /* 计算方差 */
            float accum = 0.0f;
            std::for_each(vecDistance.begin(), vecDistance.end(),
            [&](const float v) {
                accum += std::pow(v - Mean, 2);
            });
            Variance = std::sqrt(accum / (vecDistance.size() - 1));
        }

        /*
        * \brief 计算空间两点的距离
        * \param  p1 点1
        * \param  p2 点2
        * \return    两点间的空间距离
        */
        inline float __calcDistanceOf2Points(const PointT p1, const PointT p2) {
            return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2) + std::pow((p1.z - p2.z), 2));
        }

        /*
        * 在原始点云上直接等间隔取点
        * \param majorFPIndex 保存等间隔点云索引
        **/
        void __getAppropriateFP(std::vector<int> &majorFPIndex) {
            majorFPIndex.push_back(0);
            float sumDistance = 0.0f;
            PointT point = _cloud->points[0];
            for (size_t i = 1; i < _cloud->points.size(); ++i) {
                while (sumDistance < _minDistance && i < _cloud->points.size()) {
                    sumDistance += __calcDistanceOf2Points(point, _cloud->points[i]);
                    point = _cloud->points[i++];
                }
                if (i == _cloud->points.size() - 1) {
                    majorFPIndex.push_back(i);
                    break;
                } else {
                    majorFPIndex.push_back(--i);
                    sumDistance = 0.0f; /* 置零 */
                }
            }
            if (majorFPIndex.back() != _cloud->points.size() - 1)
                majorFPIndex.push_back(_cloud->points.size() - 1);
        }

        /**
        * \brief 判断一个点的类型
        * \param  point 当前点
        * \param  index 点的索引
        * \return       返回点的类型
        */
        RFPT __isFP(const PointT point, int index, bool &next_is_EdgePoint) {

            /* 情况一：跳过起点和终点 */
            if (index == 0 || index == _cloud->points.size() - 1)
                return RFPT::NormalPoint;

            /* 情况二：扫描空洞边界点 */
            float distanceNext = __calcDistanceOf2Points(_cloud->points[index], _cloud->points[index + 1]);
            float distancePre = __calcDistanceOf2Points(_cloud->points[index], _cloud->points[index - 1]);
            if (distanceNext > _mean + 2 * _variance || distancePre > _mean + 2 * _variance)
                return RFPT::EdgePoint;

            /* 情况三：直角点 */
            float deltaX = _cloud->points[index + 1].x - _cloud->points[index].x;
            float deltaY = _cloud->points[index + 1].y - _cloud->points[index].y;
            if (std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2)) / distanceNext < 0.707) { /* sqrt(2)/2 */
                next_is_EdgePoint = true;
                return RFPT::RightAnglePoint;
            }

            /* 情况四： 转折点 */
            if (std::abs(__calcAngleOf2VectorsByPointNeighbor(point, index)) < 0.9f) {
                return RFPT::InflectionPoint;
            }

            /* 情况五：极值点 */
            std::vector<int> vecID(1); std::vector<float> vecDis(1);
            int K = 20, err = 0;
            if (_kdtree.nearestKSearch(point, K, vecID, vecDis) > 0) {
                for (auto i : vecID) {
                    if (_cloud->points[i].z <= point.z)
                        err++;
                    if ((float)err / K > 0.2)
                        return RFPT::NormalPoint;
                }
                return RFPT::ExtremePoint;
            }

            /* 其他：无特征点 */
            return RFPT::NormalPoint;
        }

        /*
        * \brief 计算一个点的局部信息
        * \param point 待处理的点
        * \param index 待处理的点的索引
        * \param neighbor 选择邻域点数
        */
        float __calcAngleOf2VectorsByPointNeighbor(const PointT point, int index) {

            float n_x1 = _cloud->points[index + 1].x - point.x;
            float n_y1 = _cloud->points[index + 1].y - point.y;
            float n_z1 = _cloud->points[index + 1].z - point.z;

            float n_x2 = _cloud->points[index - 1].x - point.x;
            float n_y2 = _cloud->points[index - 1].y - point.y;
            float n_z2 = _cloud->points[index - 1].z - point.z;

            return __calcAngleOf2Vectors(n_x1, n_y1, n_z1, n_x2, n_y2, n_z2);
        }

        /*
        * \brief 计算介于两个等间隔点的特征点的索引
        * \param p1 起始点
        * \param p2 终点
        * \param vecCoarseIndex 粗糙特征点
        * \param index_from 索引游标
        * \param vecInerIndex 最终确定的特征点
        **/
        void __calcInnerIndexOf2Points(PointT p1, PointT p2, const std::vector<int> &vecCoarseIndex, int &index_from, std::vector<int> &vecSelect) {

            /* 1. 确定圆心和半径 */
            std::ofstream ooo("E:/center.txt");
            PointT center;
            center.x = (p1.x + p2.x) / 2;
            center.y = (p1.y + p2.y) / 2;
            center.z = (p1.z + p2.z) / 2;
            ooo << center.x << " " << center.y << " " << center.z << " 255 255 0" << std::endl;
            ooo.close();
            float radius = __calcDistanceOf2Points(p1, center);

            /* 2. 介于 p1 和 p2 之间的点 */
            std::vector<int> vecBetween;
            for (size_t i = index_from; i < vecCoarseIndex.size(); ++i) {
                if (__calcDistanceOf2Points(_cloud->points[vecCoarseIndex[i]], p1) <
                        __calcDistanceOf2Points(p1, p2) + _deltaZ / 10) {
                    vecBetween.push_back(vecCoarseIndex[i]);
                    continue;
                }
                index_from = i; break;
            }

            /* 3. 解析位于同侧的点 */
            if (vecBetween.size() == 0) { /* 不存在特征点则返回 */
                return;
            }

            if (vecBetween.size() == 1) { /* 存在一个特征点则保留 */
                vecSelect.push_back(vecBetween[0]);
                return;
            }

            std::vector<int> vecSameOritation; /* 存在两个以上就进行判断 */
            int flag = __computeRelativeRelation(p1, p2, _cloud->points[vecBetween[0]]);
            vecSameOritation.push_back(vecBetween[0]);
            for (size_t i = 1; i < vecBetween.size(); ++i) {
                int tempFlag = __computeRelativeRelation(p1, p2, _cloud->points[vecBetween[i]]);

                if (flag == tempFlag) {
                    vecSameOritation.push_back(vecBetween[i]);
                    if (vecSameOritation.size() != vecBetween.size()) {
                        if (i != vecBetween.size() - 1)
                            continue;
                    }
                }

                /* 在检测出的同一方向中的点中，找一个距离最远点(亦即求Z方向的极值点) */
                float maxDistance = __computePoint2LineDistance(p1, p2, _cloud->points[vecSameOritation[0]]);
                int highIndex = vecSameOritation[0];
                for (size_t j = 1; j < vecSameOritation.size(); ++j) {
                    double tempDistance = __computePoint2LineDistance(p1, p2, _cloud->points[vecSameOritation[j]]);
                    if (tempDistance > maxDistance - 0.00001) {
                        maxDistance = tempDistance;
                        highIndex = vecSameOritation[j];
                    }
                }
                vecSelect.push_back(highIndex);
                flag = __computeRelativeRelation(p1, p2, _cloud->points[vecBetween[i]]);
                std::vector<int>().swap(vecSameOritation);
                vecSameOritation.push_back(vecBetween[i]);
            }
        }

        /*
        * \brief 计算两个法向量的相对关系
        * \param from 基准向量起点
        * \param to 基准向量终点
        * \param searchPoint 第三点
        * \return 相对关系
        **/
        inline  int __computeRelativeRelation(PointT from, PointT to, PointT searchPoint) {
            float majorN = (to.z - from.z) * (searchPoint.x - from.x);
            float minorN = (to.x - from.x) * (searchPoint.z - from.z);
            if (majorN > minorN) return 1;
            return -1;
        }

        /*
        * \brief 点到空间直线的距离
        * \param from 直线的掐点
        * \param to 直线的终点
        * \param p  直线外一点
        * \return 点到点的距离
        **/
        double __computePoint2LineDistance(PointT from, PointT to, PointT p) {
            double Sft = std::sqrt(std::pow(to.x - from.x, 2) + std::pow(to.y - from.y, 2) + std::pow(to.z - from.z, 2));
            double Sfp = std::sqrt(std::pow(p.x - from.x, 2) + std::pow(p.y - from.y, 2) + std::pow(p.z - from.z, 2));
            double Spt = std::sqrt(std::pow(to.x - p.x, 2) + std::pow(to.y - p.y, 2) + std::pow(to.z - p.z, 2));
            double cosF = (std::pow(Sft, 2) + std::pow(Sfp, 2) - std::pow(Spt, 2)) / (2 * Sft * Sfp);
            double sinF = std::sqrt(1 - std::pow(cosF, 2));
            return Sft * sinF;
        }

        /*
        * \brief 优化最后的提取结果
        * \param in 精采样后的点
        */
        void __optimizeFP(std::vector<int> &in) {
            std::vector<int> vecRemove;
            float remove = _minDistance / 4;
            for (size_t i = 1; i < _vecFPIndex.size() - 1; ++i) {
                /* 当前点是否为标准分割点 */
                auto it = std::find(std::begin(in), std::end(in), i);
                if (it == std::end(in)) { /* 不是特征点，可以进行删除 */
                    /* 判断斜率 */
                    if (__calcDistanceOf2Points(_cloud->points[_vecFPIndex[i]], _cloud->points[_vecFPIndex[i + 1]]) < remove) {
                        if (__computeSlopeRatio(_cloud->points[_vecFPIndex[i]], _cloud->points[_vecFPIndex[i + 1]]) > 0.95f)
                            vecRemove.push_back(_vecFPIndex[i]);
                    } else if (__calcDistanceOf2Points(_cloud->points[_vecFPIndex[i]], _cloud->points[_vecFPIndex[i - 1]]) < remove) {
                        if (__computeSlopeRatio(_cloud->points[_vecFPIndex[i - 1]], _cloud->points[_vecFPIndex[i]]) > 0.95f)
                            vecRemove.push_back(_vecFPIndex[i]);
                    }
                }
            }
            for (auto v : vecRemove)
                _vecFPIndex.erase(std::remove(_vecFPIndex.begin(), _vecFPIndex.end(), v), _vecFPIndex.end());
        }

        /*
         * \brief 计算两点形成的坡度
         * \param p1 点1
         * \param p2 点2
         * \return 斜率
         **/
        inline float __computeSlopeRatio(PointT p1, PointT p2) {
            float distance = __calcDistanceOf2Points(p1, p2);
            float bottom = std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
            return (bottom / distance);
        }
    };

} /* LY */

/* TEST */
int main(void) {

    /* 输入点云 */
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    ///////////////////////////////////////////////////
    // 读取点云可能实现的代码
    //for (auto v : vec){
    //  pcl::PointXYZ p;
    //  p.x = v.x; p.y = v.y; p.z = v.z;
    //  cloud->points.push_back(p);
    //}
    ///////////////////////////////////////////////////

    /* 输出点云 */
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fp(new pcl::PointCloud<pcl::PointXYZ>);
    /* 提取道路切面特征点 */
    LY::RoadFPExtractor<pcl::PointXYZ> fpExtractor;
    fpExtractor.setInputCloud(cloud); /* 点云转换接口 */
    fpExtractor.setMinDistanceOfFP(2.0f); /* 设置特征点的平均间隔，单位：米，推荐值：2m */
    fpExtractor.setDeltaZField(0.3f); /* 设置特征点 Z 方向的最大高差，单位：米，推荐值：0.3m */
    fpExtractor.filterRoadFuturePoint(cloud_fp); /* 输出的点云 */

    //////////////////////////////////////////////////
    // 输出点云实现的代码
    for(auto p : cloud_fp->points)
        std::cout << p.x << ' ' << p.y << ' ' << p.z;
    //////////////////////////////////////////////////

    return 0;
}