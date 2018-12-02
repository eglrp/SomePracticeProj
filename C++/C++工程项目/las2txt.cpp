#include <iostream>
#include <iomanip>
#include <fstream>
#include "lasreader.hpp"

void las2txt() {

    //laslib只允许'\\'格式的文件路径。
    std::string lasFile("E:\\xt.las");

    //打开las文件
    LASreadOpener lasreadopener;
    lasreadopener.set_file_name(lasFile.c_str());
    LASreader *lasreader = lasreadopener.open();

    //建立输出文件
    std::ofstream ofs("output.txt");

    //遍历每行点云数据
    while (lasreader->read_point()) {
        ofs << std::setprecision(12)
            << lasreader->point.get_gps_time() << "  "  // GPS时间
            << lasreader->point.get_x() << "  "         // X
            << lasreader->point.get_y() << "  "         // Y
            << lasreader->point.get_z() << std::endl;   // Z
    }

    //关闭响应流，释放内存
    ofs.close();
    lasreader->close();
    delete lasreader;
}

int main() {
    las2txt();
    std::cout << "Successful~\n";
    return 0;
}
