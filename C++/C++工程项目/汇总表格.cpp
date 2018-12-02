#include <string>
#include <vector>
#include <io.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void getFiles( string path, vector<string> &files ) {
    long hFile = 0;  //文件句柄
    struct _finddata_t fileinfo;   //自行查看_finddata、_findfirst 和 _findnext
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            //如果是目录,迭代之，如果不是,加入列表
            if((fileinfo.attrib & _A_SUBDIR)) {
                //continue;
                if(strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
            } else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        } while(_findnext(hFile, &fileinfo) == 0); _findclose(hFile);
    }
}

void mergeTxtToCSV(vector<string> & v, string path){
    ofstream ofs(path);
    for(auto f : v){
        ifstream ifs(f);
        if(!ifs) {cout << "Open txt failed. The file is " << f << endl; continue;}
        int count = 0; char line[1024];
        while(ifs.getline(line, sizeof(line))){
            ++count;
            if(count <= 5) continue;
            stringstream ss(line);
            cout << ss.str() << endl;
            // todo ...
        }
        ifs.close();
    }
    ofs.close();
}

int main() {
    // input path
    string folder = "E:\\xiaowei";
    // define list
    vector<string> files;
    getFiles(folder, files);  //files为返回的文件名构成的字符串向量组
    // merge txt file
    mergeTxtToCSV(files, "E:/MERGE.csv");

    return 0;
}
