#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <direct.h>

using namespace std;

// void printPercent(int n, int total) {
//     int pre = (int)((float)(n + 1) / total * 100);
//     int next = 100 - pre;
//     float ratio = 0.5;
//     string sPre(pre * ratio, '=');
//     string sNext(next * ratio, '*');
//     string str = sPre + sNext;
//     cout << "\r" << " > Reading: | " << str << " | "
//          << pre << "% ( " << n << " / " << total << " )";
//     if(pre == 99)
//         cout << "\r" << " > Reading: | " << str << " | "
//              << "100% ( " << n << " / " << total << " )";
// }


// void printPercent(int n, int total) {
//     int pre = (int)((float)(n + 1) / total * 100);
//     int next = 100 - pre;
//     float ratio = 0.5;
//     string sPre(pre * ratio, '=');
//     string sNext(next * ratio, '*');
//     string str = sPre + sNext;
//     cout << "\r" << " > Reading: | " << str << " | "
//          << pre << "% ( " << n << " / " << total << " )";
//     if(pre == 99)
//         cout << "\r" << " > Reading: | " << str << " | "
//              << "100% ( " << n << " / " << total << " )";
// }

void readXYZRGB(string path) {
    // Read data from txt
    ifstream ifs(path.c_str(), ios::in);
    if(!ifs) {
        cout << " > File open failed!\n";
        return;
    } else
        cout << " > File open successful!\n";

    // Start reading
    char line[500];
    float x, y, z;
    float r, g, b;
    int num = 0;

    while(ifs.getline(line, sizeof(line))) {
        stringstream ss(line);
        ss >> x;
        ss >> y;
        ss >> z;

        ss >> r;
        ss >> g;
        ss >> b;

        cout << x << " " << y << " " << z << " " << r << " " << g << " " << b << endl;

        num++;
        if(num > 6)
            return;
    }
}

int main() {

    readXYZRGB(string("F:\\Project_Qt\\PCLFinal\\2.2-non-ground.txt"));

    return 0;
}

// // pack r/g/b into rgb
//         uint8_t r = 255, g = 0, b = 0;    // Example: Red color
//         uint32_t rgb = ((uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b);
//         p.rgb = *reinterpret_cast<float*>(&rgb);
        
//         PointXYZRGB p;
//         // unpack rgb into r/g/b
//         uint32_t rgb = *reinterpret_cast<int*>(&p.rgb);
//         uint8_t r = (rgb >> 16) & 0x0000ff;
//         uint8_t g = (rgb >> 8)  & 0x0000ff;
//         uint8_t b = (rgb)       & 0x0000ff;