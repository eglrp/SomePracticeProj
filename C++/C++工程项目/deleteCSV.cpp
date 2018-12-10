#include <string>
#include <vector>
#include <io.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

void getFileAbsolutePath(std::string path, std::vector<std::string> &file_abs_path, std::vector<std::string> &file_name ) {

    long hFile = 0;  //文件句柄
    struct _finddata_t fileinfo;   //自行查看_finddata、_findfirst 和 _findnext
    std::string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            //如果是目录,迭代之，如果不是,加入列表
            if((fileinfo.attrib & _A_SUBDIR)) {
                continue;
                if(strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFileAbsolutePath( p.assign(path).append("\\").append(fileinfo.name), file_abs_path, file_name);
            } else {
                file_abs_path.push_back(p.assign(path).append("\\").append(fileinfo.name));
                file_name.push_back(fileinfo.name);
            }
        } while(_findnext(hFile, &fileinfo) == 0); _findclose(hFile);
    }
}

void dealCSV(const std::vector<std::string> &file_abs_path, const std::vector<std::string> &file_name, std::string outputPath) {
    std::vector<std::string> ERROR_COUNT;
    std::vector<std::string> ERROR_CONTENT;
    for(int i = 0; i < file_abs_path.size(); ++i) {
        std::ifstream inFile(file_abs_path[i], std::ios::in);
        std::string lineStr;

        // Read by line
        bool flag = true;
        int count_row = 1;
        std::ofstream ofs(outputPath + "\\" + file_name[i]);
        while (getline(inFile, lineStr)) {
            std::stringstream ss(lineStr);
            std::string str;
            std::vector<std::string> lineArray;
            while (getline(ss, str, ',')) lineArray.push_back(str);
            if(lineArray.size() < 5) { // invalid file
                ERROR_CONTENT.push_back(file_name[i]);
                break;;
            }

            // Valid file
            if(flag) { // the head line copyed
                ofs << lineArray[0] << ',' << lineArray[1] << ','
                    << lineArray[2] << ',' << lineArray[6] << std::endl;
                flag = false;
                continue;
            }

            // pass the row which contains "24h" or "8h" in col 'C'
            std::string str1 = "24h"; std::string str2 = "8h";
            auto k1 = lineArray[2].find(str1);
            auto k2 = lineArray[2].find(str2);
            if(k1 != lineArray[2].npos || k2 != lineArray[2].npos)
                continue;

            // Save results
            ofs << lineArray[0] << ',' << lineArray[1] << ','
                << lineArray[2] << ',' << lineArray[6] << std::endl;
            count_row++;
        }
        inFile.close();
        ofs.close();
        if(count_row != 169)
            ERROR_COUNT.push_back(file_name[i]);
        std::cout << " > File No." << i + 1 << ": " << file_abs_path[i] << " finished\n";
    }

    // Print error file
    std::ofstream ofs(outputPath + "\\" + "ERROR_LOG.txt");
    ofs << "INVALID FILES:  " << ERROR_CONTENT.size() << std::endl;
    for(auto v : ERROR_CONTENT) {
        ofs << v << std::endl;
    }

    ofs << "WRONG FILES(NOT 169 LINES):  " << ERROR_COUNT.size() << std::endl;
    for(auto v : ERROR_COUNT) {
        ofs << v << std::endl;
    }
    ofs.close();

    // delete invalid file
    for(auto v : ERROR_CONTENT) {
        remove((outputPath + "\\" + v).c_str());
    }

}

int main() {
    clock_t start, finish;
    double totaltime;
    start = clock();

    std::string inputPath = "E:\\xiaowei";
    std::string outputPath = "E:\\xiaowei_result";
    std::vector<std::string> file_abs_path, file_name;
    getFileAbsolutePath(inputPath, file_abs_path, file_name);
    dealCSV(file_abs_path, file_name, outputPath);

    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << " > All task finished, using " << totaltime << "s.\n";

    return 0;
}
