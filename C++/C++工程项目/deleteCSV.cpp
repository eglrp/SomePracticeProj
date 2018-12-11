#include <string>
#include <vector>
#include <io.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>

namespace LY {

    class CSVOperator {
    public:

        // Constructor
        CSVOperator(std::string path, int ignoreHeadLineNum) :
            _csvFileAbsPath(path),
            _ifs(NULL),
            _ignoreLineNum(ignoreHeadLineNum),
            vecContent(std::vector<std::vector<std::string>>()),
            _maxRow(0) {
            if(!_isOpened) {
                if(openCSV(path) < 0) {
                    std::cout << "Can not create CSVOperator!\n";
                    exit(0);
                }
            }
        }

        // Descontructor
        ~CSVOperator() {
            if(_ifs)
                _ifs.close();
        }

        // Open CSV file
        int openCSV(std::string path) {
            if(!_isOpened) {
                _ifs.open(path.c_str(), std::ios::in);
                if(!_ifs) {
                    std::cout << "Can not open the file!\n";
                    return -1;
                }
                std::string lineStr; bool flag_end = false;
                while (getline(_ifs, lineStr) && !flag_end) {
                    std::stringstream ss(lineStr);
                    std::string str;
                    std::vector<std::string> lineArray;
                    while (getline(ss, str, ',')) {
                        lineArray.push_back(str);
                    }
                    if(lineArray[3].empty()) {
                        flag_end = true;
                        break;
                    }
                    vecContent.push_back(lineArray);
                    _maxRow++;
                }
                vecContent.shrink_to_fit();
                _isOpened = true;
                // std::cout << _maxRow << std::endl;
            }
            return 1;
        }

        // Get average value
        int getCSVAverageValueByGroup(int span, std::string path = "E:/LY_RESULT_CPP.csv") {
            std::ofstream ofs(path, std::ios::out | std::ios::trunc);
            if(!ofs) {
                std::cout << "Failes create " << path << std::endl;
                return -1;
            }
            // Fill first _ignoreLineNum lines
            int index = 0;
            while(index < _ignoreLineNum) {
                for(auto v : vecContent[index])
                    ofs << std::fixed << std::setprecision(3) << v << ',';
                ofs << std::endl; index++;
            }
            int startRowNum = _ignoreLineNum;
            int length = __getContinuousRow(startRowNum, span);
            while(startRowNum < _maxRow) {
                for(int j = 0; j < vecContent[startRowNum].size(); ++j) {
                    switch(j) {
                    case 0:
                        ofs << std::fixed << std::setprecision(3)
                            << vecContent[startRowNum][0] << ','; break;
                    case 1:
                        ofs << " " << ','; break;
                    case 8:
                        ofs << "---" << ','; break;
                    case 11:
                        ofs << "---" << ','; break;
                    default:
                        ofs << std::fixed << std::setprecision(3) << std::to_string(__getColAevrage(startRowNum, length, j)) << ','; break;
                    }
                }
                ofs << std::endl;
                startRowNum += length;
            }
            ofs.close();
            return 0;
        }

    private:
        std::string _csvFileAbsPath;
        std::ifstream _ifs;
        bool _isOpened;
        int _ignoreLineNum;
        std::vector<std::vector<std::string>> vecContent;
        int _maxRow;

        int __getContinuousRow(int startRowNumber, int span) {
            int count = 1;
            std::string flag_date = vecContent[startRowNumber][0];
            std::string flag_time = vecContent[startRowNumber][1].substr(0, 2);
            for(int i = startRowNumber + 1; ; ++i) {
                if(count > span)
                    break;
                if(vecContent[i][0] != flag_date ||
                        vecContent[i][1].substr(0, 2) != flag_time)
                    break;
                count++;
            }
            return count;
        }

        float __getColAevrage(int startRowNumber, int span, int col) {
            std::vector<float> v;
            for(int i = startRowNumber; span != 0; ++i, --span) {
                if(vecContent[i][col] == "---")
                    continue;
                v.push_back(atof(vecContent[i][col].c_str()));
            }
            float sum = std::accumulate(v.begin(), v.end(), 0.0f);
            return (sum / v.size());
        }
    };

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
        std::vector<std::string> {};
        for(int i = 0; i < file_abs_path.size(); ++i) {
            std::ifstream inFile(file_abs_path[i], std::ios::in);
            std::string lineStr;

            // Read by line
            bool flag = true;
            int count_row = 1;
            std::ofstream ofs_wulumuqi(outputPath + "\\wulumuqi_1194A_195\\" + file_name[i]);
            std::ofstream ofs_tiantan(outputPath + "\\tiantan_1004A_7\\" + file_name[i]);
            std::ofstream ofs_shanghai(outputPath + "\\shanghai_1146A_147\\" + file_name[i]);
            std::ofstream ofs_lasa(outputPath + "\\lasa_1654A_579\\" + file_name[i]);
            std::ofstream ofs_changchun(outputPath + "\\changchun_1124A_126\\" + file_name[i]);
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

                    ofs_wulumuqi << lineArray[0] << ',' << lineArray[1] << ','
                                 << lineArray[2] << ',' << lineArray[194] << std::endl;
                    ofs_tiantan << lineArray[0] << ',' << lineArray[1] << ','
                                << lineArray[2] << ',' << lineArray[6] << std::endl;
                    ofs_shanghai << lineArray[0] << ',' << lineArray[1] << ','
                                 << lineArray[2] << ',' << lineArray[146] << std::endl;
                    ofs_lasa << lineArray[0] << ',' << lineArray[1] << ','
                             << lineArray[2] << ',' << lineArray[578] << std::endl;
                    ofs_changchun << lineArray[0] << ',' << lineArray[1] << ','
                                  << lineArray[2] << ',' << lineArray[125] << std::endl;

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
                ofs_wulumuqi << lineArray[0] << ',' << lineArray[1] << ','
                             << lineArray[2] << ',' << lineArray[194] << std::endl;
                ofs_tiantan << lineArray[0] << ',' << lineArray[1] << ','
                            << lineArray[2] << ',' << lineArray[6] << std::endl;
                ofs_shanghai << lineArray[0] << ',' << lineArray[1] << ','
                             << lineArray[2] << ',' << lineArray[146] << std::endl;
                ofs_lasa << lineArray[0] << ',' << lineArray[1] << ','
                         << lineArray[2] << ',' << lineArray[578] << std::endl;
                ofs_changchun << lineArray[0] << ',' << lineArray[1] << ','
                              << lineArray[2] << ',' << lineArray[125] << std::endl;
                count_row++;
            }
            inFile.close();

            ofs_wulumuqi.close();
            ofs_tiantan.close();
            ofs_shanghai.close();
            ofs_lasa.close();
            ofs_changchun.close();

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
}


int main() {
    clock_t start, finish;
    double totaltime;
    start = clock();

    {
        // Select specefic rows and cols
        std::string inputPath = "E:\\xiaowei";
        std::string outputPath = "E:\\xiaowei_result";
        std::vector<std::string> file_abs_path, file_name;
        LY::getFileAbsolutePath(inputPath, file_abs_path, file_name);
        LY::dealCSV(file_abs_path, file_name, outputPath);
    }

    /*{
        // Calc average valus
        LY::CSVOperator csv("E:/xiaowei/123.csv", 2);
        if(csv.getCSVAverageValueByGroup(60) < 0) {
            std::cout << "ERROR\n";
            return -1;
        }
    }*/

    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << " > All task finished, using " << totaltime << "s.\n";

    return 0;
}