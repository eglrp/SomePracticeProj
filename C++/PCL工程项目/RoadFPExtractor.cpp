#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <io.h>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/io/io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <utility>

namespace LY {

    template<typename PointT>
    class RoadFPExtractor {
    public:
        typedef typename pcl::PCLBase<PointT>::PointCloudPtr PointCloudPtr;
        typedef typename pcl::PCLBase<PointT>::PointCloudConstPtr PointCloudConstPtr;

        /** Constructor
         * \brief initialize RoadFPExtractor object
         * \param minDistance [the minimum of 2 feature point]
         */
        RoadFPExtractor(const float minDistance = 0.5f)
            : _cloud(new pcl::PointCloud<PointT>),
              _cloud_feature(new pcl::PointCloud<PointT>) {
            _isFitted = true;
            _isOrigined = false;
            _minDistance = minDistance;
            _mean = 0.0f;
            _variance = 0.0f;
            _ratio = 0.0f;
        }

        /** Desconstrutor */
        ~RoadFPExtractor() {}

        /**
         * \brief set if optimize the feature point
         * \param opt [flag to optimize]
         */
        void setFittedFP(bool opt) {
            _isFitted = opt;
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
        void setInputCloud(const std::string path) {
            __readDataFromTxt(path);
        }

        /**
         * \brief set input point cloud
         * \param another_cloud [another point cloud]
         */
        void setInputCloud(const PointCloudConstPtr &another_cloud) {
            for(auto point : another_cloud->points) {
                std::vector<float> v;
                v.push_back(point.x); v.push_back(point.y); v.push_back(point.z);
                _vecPointCloud.push_back(v);
            }
            _vecPointCloud.shrink_to_fit();
            __sortAndFillCloud();
        }

        /**
         * Principle Component
         * \brief extract feature point
         * \param fp [the output cloud]
         */
        void filterRoadFuturePoint(PointCloudPtr &fp) {
            std::vector<int> vecInflectionPoint;
            bool next_is_EdgePoint = false;
            for(int i = 0; i < _cloud->points.size(); ++i) {
                RFPT type = __isFP(_cloud->points[i], i, next_is_EdgePoint); \
                switch(type) {
                case EdgePoint:
                    _vecFPIndex.push_back(i); break;
                case ExtremePoint:
                    _vecFPIndex.push_back(i); break;
                case InflectionPoint:
                    vecInflectionPoint.push_back(i); break;
                case NormalPoint:
                    break;
                }
                if(next_is_EdgePoint) {
                    _vecFPIndex.push_back(++i);
                    next_is_EdgePoint = false;
                    continue;
                }
            }
            vecInflectionPoint.shrink_to_fit();

            /** Sparsing the InflectionPoint */
            std::vector<int> vecInflectionPointOptimized;
            __sparseFP(vecInflectionPoint, vecInflectionPointOptimized);
            for(auto index : vecInflectionPointOptimized)
                _vecFPIndex.push_back(index);
            _vecFPIndex.shrink_to_fit();

            /** Generate feature point cloud */
            for(auto index : _vecFPIndex) {
                PointT point;
                point.x = _cloud->points[index].x;
                point.y = _cloud->points[index].y;
                point.z = _cloud->points[index].z;
                _cloud_feature->points.push_back(point);
            }

            /** Check if optimize the result */
            if(_isFitted)
                __optimizeFP(fp);
            else {
                fp->width = _cloud_feature->width; fp->height = 1;
                fp->points.resize(fp->width * fp->height);
                pcl::copyPointCloud(*_cloud_feature, *fp);
                _ratio = (int)((float)_cloud_feature->points.size() / _cloud->points.size() * 100);
            }
        }

        /**
         * \brief Get the ratio of feature point to the origin point
         */
        int getFPRatio() {
            return _ratio;
        }

    private:
        PointCloudPtr _cloud, _cloud_feature; /* Origin point cloud and feature point cloud */
        std::vector<std::vector<float>> _vecPointCloud; /* Store coordinate of origin point cloud in the two dimensional vector */
        std::vector<int> _vecFPIndex; /* The indices of feature point in the sorted origin point cloud */
        float _minDistance; /* The minimum distance of 2 feature point. The unit is meter(m) */
        float _mean, _variance; /* The adjacent distance of 2 point in sorted cloud */
        bool _isFitted, _isOrigined; /* Flag to fiting the FP and keep the origin point */
        typedef enum RoadFeaturePointType {
            EdgePoint, ExtremePoint, InflectionPoint, NormalPoint /* Custome Feature Point Type */
        } RFPT;
        float _ratio; /* The ratio of feature point to the origin point */

        /**
         * \brief read point cloud privacy
         * \param file_path [data path]
         */
        void __readDataFromTxt(const std::string path) {
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
            __calcGlobalAverageDistance(_mean, _variance);
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
        __calcAngleOf2Vectors(float x1, float y1, float z1, float x2, float y2, float z2) {
            float dot = x1 * x2 + y1 * y2 + z1 * z2;
            float square = std::sqrt(x1 * x1 + y1 * y1 + z1 * z1) * std::sqrt(x2 * x2 + y2 * y2 + z2 * z2);
            return (dot / square);
        }

        /**
         * \brief Get global Mean and Variance
         */
        void __calcGlobalAverageDistance(float &Mean, float &Variance) {
            /** Calculate distance */
            std::vector<float> vecDistance;
            for(int i = 0; i < _vecPointCloud.size() / _vecPointCloud[0].size() - 1; i++) {
                float deltaX = _vecPointCloud[i + 1][0] - _vecPointCloud[i][0];
                float deltaY = _vecPointCloud[i + 1][1] - _vecPointCloud[i][1];
                float deltaZ = _vecPointCloud[i + 1][2] - _vecPointCloud[i][2];
                float distance = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2) + std::pow(deltaZ, 2));
                vecDistance.push_back(distance);
            }
            vecDistance.shrink_to_fit();

            /** Calculate Mean */
            float sum = std::accumulate(vecDistance.begin(), vecDistance.end(), 0.0f);
            Mean = sum / vecDistance.size();

            /** Calculate Variance */
            float accum = 0.0f;
            std::for_each(vecDistance.begin(), vecDistance.end(),
            [&](const float v) {
                accum += std::pow(v - Mean, 2);
            });
            Variance = std::sqrt(accum / (vecDistance.size() - 1));
        }

        /**
         * \brief Calculate distance between two points
         * \param  p1 [point1]
         * \param  p2 [point2]
         * \return    [distance between two points]
         */
        inline  float
        __calcDistanceOf2Points(const PointT p1, const PointT p2) {
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
        RFPT __isFP(const PointT point, int index, bool &next_is_EdgePoint) {
            /**  Condition1: EdgePoint */
            if(index == 0 || index == _cloud->points.size() - 1)
                return EdgePoint;

            float distanceNext = __calcDistanceOf2Points(_cloud->points[index], _cloud->points[index + 1]);
            float distancePre = __calcDistanceOf2Points(_cloud->points[index], _cloud->points[index - 1]);
            if( distanceNext > _mean + _variance || distancePre > _mean + _variance)
                return EdgePoint;

            float deltaX = _cloud->points[index + 1].x - _cloud->points[index].x;
            float deltaY = _cloud->points[index + 1].y - _cloud->points[index].y;
            if(std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2)) / distanceNext < 0.707 ) { /* sqrt(2)/2 */
                next_is_EdgePoint = true;
                return EdgePoint;
            }

            /** Condition2: ExtremePoint (the field Z is less than neither pre or next) */
            if(_cloud->points[index + 1].z > _cloud->points[index].z &&
                    _cloud->points[index - 1].z > _cloud->points[index].z ||
                    _cloud->points[index + 1].z < _cloud->points[index].z &&
                    _cloud->points[index - 1].z < _cloud->points[index].z)
                return ExtremePoint;

            /** Contion3: InflectionPoint */
            if(std::abs(__calcAngleOf2VectorsByPointNeighbor(point, index, 2)) > 0.99f)
                return InflectionPoint;

            /** Condition4: Isolated point */
            return NormalPoint;
        }

        /**
         * \brief Sparse the feature point
         * \param in [the input point dloud index]
         * \param out [the output cloud index]
         */
        void __sparseFP(const std::vector<int> &in, std::vector<int> &out) {
            int index = in[0]; out.push_back(index);
            for(int i = 1; i < in.size(); ++i) {
                if((__calcDistanceOf2Points(_cloud->points[index], _cloud->points[in[i]])) < _minDistance / 2)
                    continue;
                index = in[i];
                out.push_back(index);
            }

            /** Check the last point */
            if(index != in[in.size() - 1] &&
                    __calcDistanceOf2Points(_cloud->points[index],
                                            _cloud->points[in[in.size() - 1]]) > _minDistance / 2)
                out.push_back(in[in.size() - 1]);
            out.shrink_to_fit();
        }

        /**
         * \brief Calculate the angle between one point neighbor
         * \param point [being dealed point]
         * \param idnex [the indice of point cloud]
         * \param neighbor [select number of neighbor points both positive and negative direction]
         */
        float __calcAngleOf2VectorsByPointNeighbor(const PointT point, int index, int neighbor = 5) {
            int index_pre = neighbor, index_next = neighbor;
            float n_x1 = 0.0f, n_y1 = 0.0f, n_z1 = 0.0f;
            while(index_next > 0 && (index + (neighbor - index_next) + 1) <= _cloud->points.size() - 1) {
                n_x1 += _cloud->points[index + neighbor - index_next + 1].x - point.x;
                n_y1 += _cloud->points[index + neighbor - index_next + 1].y - point.y;
                n_z1 += _cloud->points[index + neighbor - index_next + 1].z - point.z;
                index_next--;
            }
            n_x1 /= (neighbor - index_next); n_y1 /= (neighbor - index_next); n_z1 /= (neighbor - index_next);

            float n_x2 = 0.0f, n_y2 = 0.0f, n_z2 = 0.0f;
            while(index_pre > 0 && (index - (neighbor - index_pre) - 1) >= 0) {
                n_x2 += _cloud->points[index - (neighbor - index_pre) - 1].x - point.x;
                n_y2 += _cloud->points[index - (neighbor - index_pre) - 1].y - point.y;
                n_z2 += _cloud->points[index - (neighbor - index_pre) - 1].z - point.z;
                index_pre--;
            }
            n_x2 /= (neighbor - index_pre); n_y2 /= (neighbor - index_pre); n_z2 /= (neighbor - index_pre);
            return __calcAngleOf2Vectors(n_x1, n_y1, n_z1, n_x2, n_y2, n_z2);
        }

        /**
         * \brief Opimize the feature points
         * \param fp [output cloud]
         */
        void __optimizeFP(PointCloudPtr &fp) {
            /** VoxelGrid filter */
            pcl::VoxelGrid<PointT> sor;
            sor.setInputCloud(_cloud_feature);
            sor.setLeafSize(0.1f, 0.1f, 0.1f);
            sor.filter(*fp);
            _ratio = (int)((float)fp->points.size() / _cloud->points.size() * 100);
            if(!_isOrigined)
                return;

            /** Find the nearest 1 point in origin cloud */
            pcl::PointCloud<PointT>::Ptr cloud_temp(new pcl::PointCloud<PointT>);
            pcl::KdTreeFLANN<PointT> _kdtree;
            _kdtree.setInputCloud(_cloud);
            for(auto point : fp->points) {
                std::vector<int> vecId(1);
                std::vector<float> vecDistance(1);
                if(_kdtree.nearestKSearch(point, 1, vecId, vecDistance) > 0)
                    cloud_temp->points.push_back(_cloud->points[vecId[0]]);
            }
            pcl::copyPointCloud(*cloud_temp, *fp);
        }

    };

} /* LY */

/**
 * \brief Traverse all files in folder
 * \param path          [folder path]
 * \param file_abs_path [the abosolutely path of file]
 * \param file_name     [file name]
 */
void getFileAbsolutePath(std::string root_path,
                         std::vector<std::string> &file_abs_path,
                         std::vector<std::string> &file_name ) {

    boost::filesystem::recursive_directory_iterator itor(root_path.c_str());
    boost::filesystem::recursive_directory_iterator itEnd;
    for( ; itor != itEnd; ++itor) {
        boost::filesystem::path file_path = itor->path();

        if(boost::filesystem::is_regular_file(file_path)) {
            file_abs_path.push_back(file_path.string());
            file_name.push_back(file_path.filename().string());
        }

        if(boost::filesystem::is_directory(file_path)) {
            getFileAbsolutePath(file_path.string(), file_abs_path, file_name);
        }
    }
}

/**
 * \brief open the file end with suffix of .dat
 * \param  path  [file path]
 * \param  cloud [input point cloud]
 * \return       [flag of ifstream]
 */
int openAscIIFile(std::string path, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud) {
    std::ifstream ifs;
    ifs.open(path.c_str(), std::ios::in);
    if(!ifs) {
        std::cout << "Can not open the file!\n";
        return -1;
    }

    std::string lineStr;
    while (getline(ifs, lineStr)) {
        std::stringstream ss(lineStr);
        std::string str;
        std::vector<std::string> lineArray;
        int count = 0;
        while (getline(ss, str, ',') ) {
            if(count < 2) {
                count++;
                continue;
            }
            lineArray.push_back(str);
        }
        pcl::PointXYZ point;
        point.x = std::stod(lineArray[0].substr(2));
        point.y = std::stod(lineArray[1].substr(3));
        point.z = std::stod(lineArray[2]);
        cloud->points.push_back(point);
    }
    return 1;
}

/* TEST */
int main(void) {

    /** Traversing folder */
    std::vector<std::string> file_abs_path;
    std::vector<std::string> file_name;
    getFileAbsolutePath("F:\\lines0", file_abs_path, file_name);

    /** Read every file */
    for(auto path : file_abs_path) {

        /** Define origin point cloud */
        std::cout << "Object:  " << path << std::endl;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        openAscIIFile(path, cloud);

        /** Calculate running time */
        clock_t start, end;
        start = clock();

        /** Define RoadFPExtractor and extract FP */
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fp(new pcl::PointCloud<pcl::PointXYZ>);
        LY::RoadFPExtractor<pcl::PointXYZ> fpExtractor; /* Define the RoadFPExtractor */
        fpExtractor.setInputCloud(cloud); /* Set input cloud */
        fpExtractor.setMinDistanceOfFP(0.5f); /** Set minimum distacne */
        fpExtractor.setFittedFP(true); /* If fiting the result */
        fpExtractor.setKeepOrigin(true); /* If keep the feature point is the origin point */
        fpExtractor.filterRoadFuturePoint(cloud_fp); /* Set the  */

        /** Calculate running time */
        end = clock();
        double during = (double)(end - start) / CLOCKS_PER_SEC;
        std::cout << "Road feature points extracted! Using " << during << "s!" << std::endl;
        std::cout << "The ratio is: " << fpExtractor.getFPRatio() << "%" << std::endl;

        /** Print result */
        std::ofstream ofs1("C:/Users/Administrator/Desktop/1.txt");
        for(auto p : cloud->points) {
            ofs1 << p.x << " " << p.y << " " << p.z << std::endl;
        }
        ofs1.close();

        std::ofstream ofs2("C:/Users/Administrator/Desktop/2.txt");
        for(auto p : cloud_fp->points) {
            ofs2 << p.x << " " << p.y << " " << p.z << std::endl;
        }
        ofs2.close();

        /** Pause the program */
        int a; std::cout << "Press any kry to conyinue:\n";
        std::cin >> a;
        if (a == 666)
            break;
        std::cout << "\n--------------------------------------------------------\n\n";
    }

    return 0;
}
