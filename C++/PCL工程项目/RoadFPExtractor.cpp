#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/io/io.h>
#include <pcl/filters/voxel_grid.h>

namespace LY {

    template<typename PointT>
    class RoadFPExtractor {
    public:
        typedef typename pcl::PCLBase<PointT>::PointCloudPtr PointCloudPtr;
        typedef typename pcl::PCLBase<PointT>::PointCloudConstPtr PointCloudConstPtr;

        /** Constructor
         * \brief initialize RoadFPExtractor object
         * \param radius [set searching radius of each point]
         */
        RoadFPExtractor(float radius = 2.0)
            : _cloud(new pcl::PointCloud<PointT>),
              _cloud_feature(new pcl::PointCloud<PointT>) {
            _radius = radius;
            _optimized = true;
            _isOrigined = false;
            _minDistance = 0.5f;
        }

        /** Desconstrutor */
        ~RoadFPExtractor() {}

        /**
         * \brief reset the radius of searching
         * \param radius [reset radius]
         */
        void setFilterRadius(float radius) {
            _radius = radius;
        }

        /**
         * \brief set if optimize the feature point
         * \param opt [flag to optimize]
         */
        void setOptimized(bool opt) {
            _optimized = opt;
        }

        /**
         * \brief Set if the feature point must be the origin road point
         * \param isOrigined [flag to keep origin point as feature point]
         */
        void setKeepOrigin(bool isOrigined) {
            _isOrigined = isOrigined;
        }

        /**
         * \brief Set the distance between two feature points
         * \param distance [set the min distance between two feature points]
         */
        void setMinDistanceOfFP(float distance) {
            _minDistance = distance;
        }

        /**
         * \brief set input point cloud
         * \param path [the txt file path]
         */
        void setInputCloud(std::string path) {
            __readDataFromTxt(path);
            _kdtree.setInputCloud(_cloud);
        }

        /**
         * \brief set input point cloud
         * \param another_cloud [another point cloud]
         */
        void setInputCloud(const PointCloudConstPtr &another_cloud) {
            for(auto point : another_cloud->points) {
                std::vector<float> v;
                v.push_back(point.x);
                v.push_back(point.y);
                v.push_back(point.z);
                _vecPointCloud.push_back(v);
            }
            _vecPointCloud.shrink_to_fit();
            __sortAndFillCloud();
            _kdtree.setInputCloud(_cloud);
        }

        /**
         * Principle Component
         * \brief extract feature point
         * \param fp [the output cloud]
         */
        void filterRoadFuturePoint(PointCloudPtr &fp) {
            for(int i = 0; i < _cloud->points.size(); ++i) {
                RFPT type = __isFP(_cloud->points[i], i); \
                bool flag_used = false;
                switch(type) {
                case EdgePoint:
                    flag_used = true; break;
                case InflectionPoint:
                    flag_used = true; break;
                case ExtremePoint:
                    flag_used = true; break;
                case IsolatedPoint:
                    flag_used = false; break;
                }
                if(flag_used) {
                    PointT point;
                    point.x = _cloud->points[i].x;
                    point.y = _cloud->points[i].y;
                    point.z = _cloud->points[i].z;
                    _cloud_feature->points.push_back(point);
                }
            }

            if(_optimized)
                __optimizeFP(fp);
            else {
                fp->width = _cloud_feature->width; fp->height = 1;
                fp->points.resize(fp->width * fp->height);
                pcl::copyPointCloud(*_cloud_feature, *fp);
            }
        }

    private:
        PointCloudPtr _cloud, _cloud_feature;
        std::vector<std::vector<float>> _vecPointCloud;
        pcl::KdTreeFLANN<PointT> _kdtree;
        float _radius, _minDistance;
        bool _optimized, _isOrigined;

        typedef enum RoadFeaturePointType {
            EdgePoint, InflectionPoint, ExtremePoint, IsolatedPoint
        } RFPT;

        /**
         * \brief read point cloud privacy
         * \param file_path [src path]
         */
        void __readDataFromTxt(std::string path) {
            std::ifstream ifs(path);
            if (!ifs) {
                std::cout << "The txt file is not existed !" << std::endl;
                return;
            }

            std::string x, y, z; char line[500];
            while(ifs.getline(line, sizeof(line))) {
                std::stringstream ss(line);
                ss >> x; ss >> y; ss >> z;
                std::vector<float> v;
                v.push_back(std::stod(x.c_str()));
                v.push_back(std::stod(y.c_str()));
                v.push_back(std::stod(z.c_str()));
                _vecPointCloud.push_back(v);
            }
            _vecPointCloud.shrink_to_fit();
            ifs.close();
            __sortAndFillCloud();
        }

        /**
         * \brief sort the point cloud ascendly and fill the cloud
         */
        void __sortAndFillCloud() {
            struct {
                bool operator()(std::vector<float> v1, std::vector<float> v2) {
                    return v1[0] < v2[0];
                }
            } customeCoordiateLess;

            std::sort(_vecPointCloud.begin(), _vecPointCloud.end(), customeCoordiateLess);
            for(auto v : _vecPointCloud) {
                PointT point;
                point.x = v[0]; point.y = v[1]; point.z = v[2];
                _cloud->points.push_back(point);
            }
        }

        /**
         * \brief calculate the angle of two vector
         * \param x1
         * \param y1
         * \param z1
         * \param x2
         * \param y2
         * \param z2
         */
        inline float
        __calcAngle(float x1, float y1, float z1, float x2, float y2, float z2) {
            float dot = x1 * x2 + y1 * y2 + z1 * z2;
            float square = std::sqrt(x1 * x1 + y1 * y1 + z1 * z1) * std::sqrt(x2 * x2 + y2 * y2 + z2 * z2);
            return (dot / square);
        }

        /**
         * \brief Calculate distance between two points
         * \param  p1 [point1]
         * \param  p2 [point2]
         * \return    [distance between two points]
         */
        inline  float
        __getDistance(PointT p1, PointT p2) {
            return std::sqrt(std::pow((p1.x - p2.x), 2) +
                             std::pow((p1.y - p2.y), 2) +
                             std::pow((p1.z - p2.z), 2));
        }

        /**
         * \brief Dertemine if a point is a future point
         * \param  point [focus point]
         * \param  index [index of the point]
         * \return       [the type of feature]
         */
        RFPT __isFP(PointT point, int index) {
            /**  Condition1: EdgePoint */
            if(index == 0 || index == _cloud->points.size() - 1)
                return EdgePoint;
            if(__getDistance(_cloud->points[index], _cloud->points[index - 1]) > 0.3 ||
                    __getDistance(_cloud->points[index], _cloud->points[index + 1]) > 0.3)
                return EdgePoint;

            /** Contion2: InflectionPoint */
            int nearest = 20;
            int index_pre = nearest, index_next = nearest;
            float n_x1 = 0.0f, n_y1 = 0.0f, n_z1 = 0.0f;
            while(index_next > 0 && (index + (nearest - index_next) + 1) <= _cloud->points.size() - 1) {
                n_x1 += _cloud->points[index + nearest - index_next + 1].x - point.x;
                n_y1 += _cloud->points[index + nearest - index_next + 1].y - point.y;
                n_z1 += _cloud->points[index + nearest - index_next + 1].z - point.z;
                index_next--;
            }
            n_x1 /= (nearest - index_next); n_y1 /= (nearest - index_next); n_z1 /= (nearest - index_next);

            float n_x2 = 0.0f, n_y2 = 0.0f, n_z2 = 0.0f;
            while(index_pre > 0 && (index - (nearest - index_pre) - 1) >= 0) {
                n_x2 += _cloud->points[index - (nearest - index_pre) - 1].x - point.x;
                n_y2 += _cloud->points[index - (nearest - index_pre) - 1].y - point.y;
                n_z2 += _cloud->points[index - (nearest - index_pre) - 1].z - point.z;
                index_pre--;
            }
            n_x2 /= (nearest - index_pre); n_y2 /= (nearest - index_pre); n_z2 /= (nearest - index_pre);

            float cosAngle = __calcAngle(n_x1, n_y1, n_z1, n_x2, n_y2, n_z2);
            if(std::abs(cosAngle) < 0.4)
                return InflectionPoint;

            /** Condition3: ExtremePoint(the higher Z or lower Z is more than 80 percent) */
            std::vector<int> vecId;
            std::vector<float> vecDistance;
            if(_kdtree.nearestKSearch(point, _radius, vecId, vecDistance) > 0) {
                int count_higher = 0, count_lower = 0;
                for(auto p : vecId) {
                    if(_cloud->points[p].z > point.z) {
                        count_higher++;
                        continue;
                    }
                    count_lower++;
                }
                if((float)count_higher / vecId.size() > 0.8f || (float)count_lower / vecId.size() > 0.8f)
                    return ExtremePoint;
            }

            /** Condition4: Isolated point */
            return IsolatedPoint;
        }

        /**
         * \brief Opimize the feature points
         * \param fp [output cloud]
         */
        void __optimizeFP(PointCloudPtr &fp) {
            // VoxelGrid filter
            pcl::VoxelGrid<PointT> sor;
            sor.setInputCloud(_cloud_feature);
            sor.setLeafSize(_minDistance, _minDistance, _minDistance);
            sor.filter(*fp);
            if(!_isOrigined)
                return;

            /** Find the nearest 1 point in origin cloud */
            pcl::PointCloud<PointT>::Ptr cloud_temp(new pcl::PointCloud<PointT>);
            for(auto point : fp->points) {
                std::vector<int> vecId(1);
                std::vector<float> vecDistance(1);
                if(_kdtree.nearestKSearch(point, 1, vecId, vecDistance) > 0)
                    cloud_temp->points.push_back(_cloud->points[vecId[0]]);
            }
            pcl::copyPointCloud(*cloud_temp, *fp);
        }

    };

}

/** TEST */
int main(void) {
    clock_t start, end;
    start = clock();

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fp(new pcl::PointCloud<pcl::PointXYZ>);

    LY::RoadFPExtractor<pcl::PointXYZ> fpExtractor;
    fpExtractor.setInputCloud("C:/Users/Administrator/Desktop/in.txt");
    fpExtractor.setFilterRadius(2.0f); // recomend
    fpExtractor.setOptimized(true);
    fpExtractor.setKeepOrigin(false);
    fpExtractor.setMinDistanceOfFP(0.5f);
    fpExtractor.filterRoadFuturePoint(cloud_fp);

    std::ofstream ofs("C:/Users/Administrator/Desktop/out.txt");
    for(auto point : cloud_fp->points )
        ofs << point.x << " " << point.y << " " << point.z << std::endl;
    ofs.close();

    end = clock();
    double during = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Road feature points extracted! Using " << during << "s!" << std::endl;
}
