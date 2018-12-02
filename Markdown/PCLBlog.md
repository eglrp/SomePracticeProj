@[toc]


## 说明
---

**欢迎进群探讨 PCL 的更多问题，期待你的加入**

**QQ群号：190162198**
**QQ群名：PCL点云部落**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20181202171934946.png)


## PCL 的安装与配置
------

 > **关于 PCL 的配置与安装请参考我得另一篇博客：[PCL+VS+Qt+Win10 的综合配置精华](https://blog.csdn.net/qq_34719188/article/details/80601642)**

## 随机点云的生成(以 pcl::PointXYZ 为例)
----

```c
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

void createRandomPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud) {
    cloud->width = 5;
    cloud->height = 1;
    cloud->is_dense = false; // 判断points中的数据是否是有限的(有限为true)或者说是判断点云中的点是否包含 Inf/NaN这种值(包含为false)
    cloud->points.resize(cloud->width * cloud->height);
    for(size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
    }
}
```

## 点云文件的 IO 操作
----

### PCD 点云的读与写(以 pcl::PointXYZ 为例)
 
```c
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

void readPointCloudFromPCD1(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, std::string file_path) {
    if(pcl::io::loadPCDFile<pcl::PointXYZ>(file_path, *cloud) == -1)
        PCL_ERROR("Couldn't read file!\n");
}

void savePointCloud2PCD1(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, std::string file_path) {
    pcl::io::savePCDFileASCII(file_path, *cloud);
}

void readPointCloudFromPCD2(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, std::string file_path) {
    pcl::PCDReader reader;
    reader.read<pcl::PointXYZ>(file_path, *cloud);
}

void savePointCloud2PCD2(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, std::string file_path) {
    pcl::PCDWriter writer;
    writer.write<pcl::PointXYZ>(file_path, *cloud);
}
```

### TXT 点云的读与写(以 pcl::PointXYZRGB 为例)


```c
#include <sstream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

void readXYZRGBFromTxt(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud, std::string file_path) {
    std::ifstream ifs(file_path);
    if (!ifs) {
        std::cout << "The txt file is not existed !" << std::endl;
        return;
    }
    float x, y, z, r, g, b; uint8_t ur, ug, ub; char line[500];
    while(ifs.getline(line, sizeof(line))) {
        std::stringstream ss(line);
        ss >> x; ss >> y; ss >> z; ss >> r; ss >> g; ss >> b;
        ur = (uint8_t)r; ug = (uint8_t)g; ub = (uint8_t)b;
        pcl::PointXYZRGB point;
        point.x = x; point.y = y; point.z = z;
        uint32_t rgb = ((uint32_t)ur << 16 | (uint32_t)ug << 8 | (uint32_t)ub);
        point.rgb = *reinterpret_cast<float *>(&rgb);
        cloud->points.push_back(point);
    }
    ifs.close();
}

void writePointCloud2Txt(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud, std::string file_path) {
    std::ofstream ofs(file_path);
    if(!ofs) {
        std::cout << "Create txt file failed!\n";
        return;
    }
    for(size_t i = 0; i < cloud->points.size (); ++i) {
        uint32_t rgb = *reinterpret_cast<int *>(&cloud->points[i].rgb);
        uint8_t r = (rgb >> 16) & 0x0000ff;
        uint8_t g = (rgb >> 8)  & 0x0000ff;
        uint8_t b = (rgb)       & 0x0000ff;
        ofs << cloud->points[i].x << " " << cloud->points[i].y << " " << cloud->points[i].z << " "
            << (int)r << " " << (int)g << " " << (int)b << std::endl;
    }
    ofs.close();
}
```

## 连接两个点云的字段
------

```c
{
    pcl::PointCloud<pcl::PointXYZ> xyz_a, xyz_b, xyz_c;
    pcl::PointCloud<pcl::Normal> normal;
    pcl::PointCloud<pcl::PointNormal> xyz_normal;
    // 点云的扩展
    xyz_c = xyz_b + xyz_b;
    // 扩充字段
    pcl::concatenateFields(xyz_a, normal, xyz_normal);
}
```

### 随机噪音的产生
-----

```c
{
    // 随机噪音
    boost::mt19937 rng;
    rng.seed(static_cast<unsigned int> (time(0)));
    boost::normal_distribution<> nd(0, 0.01);
    boost::variate_generator<boost::mt19937 &, boost::normal_distribution<>> var_nor(rng, nd);

    floa noise = static_cast<float> (var_nor());
}
```

### kd-tree
-----

```c
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <vector>

{
    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
    kdtree.setInputCloud (cloud);
    pcl::PointXYZ searchPoint;
    searchPoint.x = 1024.0f * rand () / (RAND_MAX + 1.0f);
    searchPoint.y = 1024.0f * rand () / (RAND_MAX + 1.0f);
    searchPoint.z = 1024.0f * rand () / (RAND_MAX + 1.0f);
    // K 临近搜索
    int K = 10;
    std::vector<int> pointIdxNKNSearch(K); //存储查询点近邻索引
    std::vector<float> pointNKNSquaredDistance(K); //存储近邻点对应距离平方
    //打印相关信息
    if ( kdtree.nearestKSearch (searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 ) { //执行K近邻搜索
        //打印所有近邻坐标
        for (size_t i = 0; i < pointIdxNKNSearch.size (); ++i)
            std::cout << "    "  << cloud->points[ pointIdxNKNSearch[i] ].x
                      << " " << cloud->points[ pointIdxNKNSearch[i] ].y
                      << " " << cloud->points[ pointIdxNKNSearch[i] ].z
                      << " (squared distance: " << pointNKNSquaredDistance[i] << ")" << std::endl;
    }
}


{
    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
    kdtree.setInputCloud (cloud);
    pcl::PointXYZ searchPoint;
    searchPoint.x = 1024.0f * rand () / (RAND_MAX + 1.0f);
    searchPoint.y = 1024.0f * rand () / (RAND_MAX + 1.0f);
    searchPoint.z = 1024.0f * rand () / (RAND_MAX + 1.0f);
    // 半径 R内近邻搜索方法
    std::vector<int> pointIdxRadiusSearch; //存储近邻索引
    std::vector<float> pointRadiusSquaredDistance; //存储近邻对应距离的平方
    float radius = 256.0f * rand () / (RAND_MAX + 1.0f);   //随机的生成某一半径
    if ( kdtree.radiusSearch (searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0 ) { //执行半径R内近邻搜索方法
        for (size_t i = 0; i < pointIdxRadiusSearch.size (); ++i)
            std::cout << "    "  <<   cloud->points[ pointIdxRadiusSearch[i] ].x
                      << " " << cloud->points[ pointIdxRadiusSearch[i] ].y
                      << " " << cloud->points[ pointIdxRadiusSearch[i] ].z
                      << " (squared distance: " << pointRadiusSquaredDistance[i] << ")" << std::endl;
    }
}
```

### 利用八叉树进行点云压缩

---

```c
#include <pcl/point_cloud.h>                         // 点云类型
#include <pcl/point_types.h>                          //点数据类型
#include <pcl/io/openni_grabber.h>                    //点云获取接口类
#include <pcl/visualization/cloud_viewer.h>            //点云可视化类

#include <pcl/compression/octree_pointcloud_compression.h>   //点云压缩类

#include <stdio.h>
#include <sstream>
#include <stdlib.h>

#ifdef WIN32
# define sleep(x) Sleep((x)*1000)
#endif

class SimpleOpenNIViewer
{
public:
  SimpleOpenNIViewer () :
    viewer (" Point Cloud Compression Example")
  {
  }
/************************************************************************************************
  在OpenNIGrabber采集循环执行的回调函数cloud_cb_中，首先把获取的点云压缩到stringstream缓冲区，下一步就是解压缩，
  它对压缩了的二进制数据进行解码，存储在新的点云中解码了点云被发送到点云可视化对象中进行实时可视化
*************************************************************************************************/
  
 void  cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
  {
    if (!viewer.wasStopped ())
    {
      // 存储压缩点云的字节流对象
      std::stringstream compressedData;
      // 存储输出点云
      pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloudOut (new pcl::PointCloud<pcl::PointXYZRGBA> ());

      // 压缩点云
      PointCloudEncoder->encodePointCloud (cloud, compressedData);

      // 解压缩点云
      PointCloudDecoder->decodePointCloud (compressedData, cloudOut);


      // 可视化解压缩的点云
      viewer.showCloud (cloudOut);
    }
  }
/**************************************************************************************************************
 在函数中创建PointCloudCompression类的对象来编码和解码，这些对象把压缩配置文件作为配置压缩算法的参数
 所提供的压缩配置文件为OpenNI兼容设备采集到的点云预先确定的通用参数集，本例中使用MED_RES_ONLINE_COMPRESSION_WITH_COLOR
 配置参数集，用于快速在线的压缩，压缩配置方法可以在文件/io/include/pcl/compression/compression_profiles.h中找到，
  在PointCloudCompression构造函数中使用MANUAL——CONFIGURATION属性就可以手动的配置压缩算法的全部参数
******************************************************************************************************************/
  void run ()
  {

    bool showStatistics = true;  //设置在标准设备上输出打印出压缩结果信息

    // 压缩选项详情在: /io/include/pcl/compression/compression_profiles.h
    pcl::io::compression_Profiles_e compressionProfile = pcl::io::MED_RES_ONLINE_COMPRESSION_WITH_COLOR;

    // 初始化压缩和解压缩对象  其中压缩对象需要设定压缩参数选项，解压缩按照数据源自行判断
    PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA> (compressionProfile, showStatistics);
    PointCloudDecoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA> ();
    /***********************************************************************************************************
    下面的代码为OpenNI兼容设备实例化一个新的采样器，并且启动循环回调接口，每从设备获取一帧数据就回调函数一次，，这里的
    回调函数就是实现数据压缩和可视化解压缩结果。
   ************************************************************************************************************/
    //创建从OpenNI获取点云的抓取对象
    pcl::Grabber* interface = new pcl::OpenNIGrabber ();

    // 建立回调函数
    boost::function<void
    (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f = boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1);

    //建立回调函数和回调信息的绑定
    boost::signals2::connection c = interface->registerCallback (f);

    // 开始接受点云的数据流
    interface->start ();

    while (!viewer.wasStopped ())
    {
      sleep (1);
    }

    interface->stop ();

    // 删除压缩与解压缩的实例
    delete (PointCloudEncoder);
    delete (PointCloudDecoder);

  }

  pcl::visualization::CloudViewer viewer;

  pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA>* PointCloudEncoder;
  pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA>* PointCloudDecoder;

};

int
main (int argc, char **argv)
{
  SimpleOpenNIViewer v;  //创建一个新的SimpleOpenNIViewer  实例并调用他的run方法
  v.run ();

  return (0);
}
```


### 八叉树的学习

----

```c
#include <pcl/point_cloud.h>                         // 点云类型
#include <pcl/point_types.h>                          //点数据类型
#include <pcl/io/openni_grabber.h>                    //点云获取接口类
#include <pcl/visualization/cloud_viewer.h>            //点云可视化类

#include <pcl/compression/octree_pointcloud_compression.h>   //点云压缩类

#include <stdio.h>
#include <sstream>
#include <stdlib.h>

#ifdef WIN32
# define sleep(x) Sleep((x)*1000)
#endif

class SimpleOpenNIViewer
{
public:
  SimpleOpenNIViewer () :
    viewer (" Point Cloud Compression Example")
  {
  }
/************************************************************************************************
  在OpenNIGrabber采集循环执行的回调函数cloud_cb_中，首先把获取的点云压缩到stringstream缓冲区，下一步就是解压缩，
  它对压缩了的二进制数据进行解码，存储在新的点云中解码了点云被发送到点云可视化对象中进行实时可视化
*************************************************************************************************/
  
 void  cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
  {
    if (!viewer.wasStopped ())
    {
      // 存储压缩点云的字节流对象
      std::stringstream compressedData;
      // 存储输出点云
      pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloudOut (new pcl::PointCloud<pcl::PointXYZRGBA> ());

      // 压缩点云
      PointCloudEncoder->encodePointCloud (cloud, compressedData);

      // 解压缩点云
      PointCloudDecoder->decodePointCloud (compressedData, cloudOut);


      // 可视化解压缩的点云
      viewer.showCloud (cloudOut);
    }
  }
/**************************************************************************************************************
 在函数中创建PointCloudCompression类的对象来编码和解码，这些对象把压缩配置文件作为配置压缩算法的参数
 所提供的压缩配置文件为OpenNI兼容设备采集到的点云预先确定的通用参数集，本例中使用MED_RES_ONLINE_COMPRESSION_WITH_COLOR
 配置参数集，用于快速在线的压缩，压缩配置方法可以在文件/io/include/pcl/compression/compression_profiles.h中找到，
  在PointCloudCompression构造函数中使用MANUAL——CONFIGURATION属性就可以手动的配置压缩算法的全部参数
******************************************************************************************************************/
  void run ()
  {

    bool showStatistics = true;  //设置在标准设备上输出打印出压缩结果信息

    // 压缩选项详情在: /io/include/pcl/compression/compression_profiles.h
    pcl::io::compression_Profiles_e compressionProfile = pcl::io::MED_RES_ONLINE_COMPRESSION_WITH_COLOR;

    // 初始化压缩和解压缩对象  其中压缩对象需要设定压缩参数选项，解压缩按照数据源自行判断
    PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA> (compressionProfile, showStatistics);
    PointCloudDecoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA> ();
    /***********************************************************************************************************
    下面的代码为OpenNI兼容设备实例化一个新的采样器，并且启动循环回调接口，每从设备获取一帧数据就回调函数一次，，这里的
    回调函数就是实现数据压缩和可视化解压缩结果。
   ************************************************************************************************************/
    //创建从OpenNI获取点云的抓取对象
    pcl::Grabber* interface = new pcl::OpenNIGrabber ();

    // 建立回调函数
    boost::function<void
    (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f = boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1);

    //建立回调函数和回调信息的绑定
    boost::signals2::connection c = interface->registerCallback (f);

    // 开始接受点云的数据流
    interface->start ();

    while (!viewer.wasStopped ())
    {
      sleep (1);
    }

    interface->stop ();

    // 删除压缩与解压缩的实例
    delete (PointCloudEncoder);
    delete (PointCloudDecoder);

  }

  pcl::visualization::CloudViewer viewer;

  pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA>* PointCloudEncoder;
  pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA>* PointCloudDecoder;

};

int
main (int argc, char **argv)
{
  SimpleOpenNIViewer v;  //创建一个新的SimpleOpenNIViewer  实例并调用他的run方法
  v.run ();

  return (0);
}
```

![八叉树实例图片](http://img.blog.csdn.net/20180125172857682?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzQ3MTkxODg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

> **本片段未能测试成功，貌似要采集点云**


### 可视化（经典圆球测试）


----
```c
#include <pcl/visualization/cloud_viewer.h>   //类cloud_viewer头文件申明
#include <iostream>                           //标准输入输出头文件申明
#include <pcl/io/io.h>                        //I/O相关头文件申明
#include <pcl/io/pcd_io.h>                    //PCD文件读取
    

/**********************************************************************************
  函数是作为回调函数，在主函数中只注册一次 ，函数实现对可视化对象背景颜色的设置，添加一个圆球几何体
*********************************************************************************/
int user_data;
    
void 
viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (1.0, 0.5, 1.0);       //设置背景颜色
    pcl::PointXYZ o;                                  //存储球的圆心位置
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    viewer.addSphere (o, 0.25, "sphere", 0);                  //添加圆球几何对象
    std::cout << "i only run once" << std::endl;
    
}
   /***********************************************************************************
   作为回调函数，在主函数中注册后每帧显示都执行一次，函数具体实现在可视化对象中添加一个刷新显示字符串
   *************************************************************************************/ 
void 
viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape ("text", 0);
    viewer.addText (ss.str(), 200, 300, "text", 0);
    
    //FIXME: possible race condition here:
    user_data++;
}
  /**************************************************************
  首先加载点云文件到点云对象，并初始化可视化对象viewer，注册上面的回
   调函数，执行循环直到收到关闭viewer的消息退出程序
   *************************************************************/  
int 
main ()
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);    //声明cloud 
    pcl::io::loadPCDFile ("my_point_cloud.pcd", *cloud);         //加载点云文件
    
    pcl::visualization::CloudViewer viewer("Cloud Viewer");      //创建viewer对象
    
    //showCloud函数是同步的，在此处等待直到渲染显示为止
    viewer.showCloud(cloud);
    
    //该注册函数在可视化的时候只执行一次
    viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
    //该注册函数在渲染输出时每次都调用
    viewer.runOnVisualizationThread (viewerPsycho);
    while (!viewer.wasStopped ())
    {
    //此处可以添加其他处理
    //FIXME: Note that this is running in a separate thread from viewerPsycho
    //and you should guard against race conditions yourself...
    user_data++;
    }
    return 0;
}
```



### 基于octree的空间划分及搜索操作


----

```c
#include <pcl/point_cloud.h>
#include <pcl/octree/octree.h>

#include <iostream>
#include <vector>
#include <ctime>

int
main (int argc, char** argv)
{
  srand ((unsigned int) time (NULL));  //用系统时间初始化随机种子

  // 八叉树的分辨率，即体素的大小
  float resolution = 32.0f;

  // 初始化空间变化检测对象
  pcl::octree::OctreePointCloudChangeDetector<pcl::PointXYZ> octree (resolution);

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloudA (new pcl::PointCloud<pcl::PointXYZ> );  //创建点云实例cloudA生成的点云数据用于建立八叉树octree对象

  // 为cloudA点云填充点数据
  cloudA->width = 128;                      //设置点云cloudA的点数
  cloudA->height = 1;                          //无序点
  cloudA->points.resize (cloudA->width * cloudA->height);   //总数

  for (size_t i = 0; i < cloudA->points.size (); ++i)         //循环填充
  {
    cloudA->points[i].x = 64.0f * rand () / (RAND_MAX + 1.0f);
    cloudA->points[i].y = 64.0f * rand () / (RAND_MAX + 1.0f);
    cloudA->points[i].z = 64.0f * rand () / (RAND_MAX + 1.0f);
  }

  // 添加点云到八叉树中，构建八叉树
  octree.setInputCloud (cloudA);  //设置输入点云
  octree.addPointsFromInputCloud ();   //从输入点云构建八叉树
   /***********************************************************************************
    点云cloudA是参考点云用其建立的八叉树对象描述它的空间分布，octreePointCloudChangeDetector
    类继承自Octree2BufBae类，Octree2BufBae类允许同时在内存中保存和管理两个octree，另外它应用了内存池
    该机制能够重新利用已经分配了的节点对象，因此减少了在生成点云八叉树对象时昂贵的内存分配和释放操作
    通过访问 octree.switchBuffers ()重置八叉树 octree对象的缓冲区，但把之前的octree数据仍然保留在内存中
   ************************************************************************************/
  // 交换八叉树的缓冲，但是CloudA对应的八叉树结构仍然在内存中
  octree.switchBuffers ();
  //cloudB点云用于建立新的八叉树结构，与前一个cloudA对应的八叉树共享octree对象，同时在内存中驻留
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloudB (new pcl::PointCloud<pcl::PointXYZ> );   //实例化点云对象cloudB
   
  // 为cloudB创建点云 
  cloudB->width = 128;
  cloudB->height = 1;
  cloudB->points.resize (cloudB->width * cloudB->height);

  for (size_t i = 0; i < cloudB->points.size (); ++i)
  {
    cloudB->points[i].x = 64.0f * rand () / (RAND_MAX + 1.0f);
    cloudB->points[i].y = 64.0f * rand () / (RAND_MAX + 1.0f);
    cloudB->points[i].z = 64.0f * rand () / (RAND_MAX + 1.0f);
  }

  // 添加cloudB到八叉树中
  octree.setInputCloud (cloudB);
  octree.addPointsFromInputCloud ();
  
  /**************************************************************************************************************
  为了检索获取存在于couodB的点集R，此R并没有cloudA中的元素，可以调用getPointIndicesFromNewVoxels方法，通过探测两个八叉树之间
  体素的不同，它返回cloudB 中新加点的索引的向量，通过索引向量可以获取R点集  很明显这样就探测了cloudB相对于cloudA变化的点集，但是只能探测
  到在cloudA上增加的点集，二不能探测减少的
****************************************************************************************************************/

  
  std::vector<int> newPointIdxVector;  //存储新添加的索引的向量

  // 获取前一cloudA对应八叉树在cloudB对应在八叉树中没有的点集
  octree.getPointIndicesFromNewVoxels (newPointIdxVector);

  // 打印点集
  std::cout << "Output from getPointIndicesFromNewVoxels:" << std::endl;
  for (size_t i = 0; i < newPointIdxVector.size (); ++i)
    std::cout << i << "# Index:" << newPointIdxVector[i]
              << "  Point:" << cloudB->points[newPointIdxVector[i]].x << " "
              << cloudB->points[newPointIdxVector[i]].y << " "
              << cloudB->points[newPointIdxVector[i]].z << std::endl;

}
```

### PCL点云类型的转换

----

```c
#include <pcl/common/impl/io.h>
    // ...
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz (new pcl::PointCloud<pcl::PointXYZ> ());  
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_xyzrgba (new pcl::PointCloud<pcl::PointXYZRGBA> ());
    pcl::copyPointCloud(*cloud_xyz, *cloud_xyzrgba);
    // ...
```

也可以自行手动转换



### 编译PCL遇到的错误

----

#### Q1: warning C4003: “max”宏的实参不足 | warning C4003: “min”宏的实参不足

双击进入对应的额头文件，将MAX前边的内容用括号括起来，见下：
修改前：

```c
KNNSimpleResultSet(size_t capacity_) :
        capacity_(capacity_)
    {
        // reserving capacity to prevent memory re-allocations
        dist_index_.resize(capacity_, DistIndex(std::numeric_limits<DistanceType>::max(),-1));
        clear();
    }
```

修改后：

```c
KNNSimpleResultSet(size_t capacity_) :
        capacity_(capacity_)
    {
        // reserving capacity to prevent memory re-allocations
        dist_index_.resize(capacity_, DistIndex((std::numeric_limits<DistanceType>::max)(),-1));
        clear();
    }
```

#### Q2: warning C4819：...(936)

双击报错信息进入该文件，全选中该文件，然后点击文件 - 高级保存选项 - 存为 **UNICODE 代码页 1200** 即可

#### Q3: ......