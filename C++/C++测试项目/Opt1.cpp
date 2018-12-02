#include <getopt.h>
#include <iostream>


using std::cout;
using std::endl;


int main(int argc, char *argv[]) {
    int c;

    //定义长参数选项，如--file
    static struct option long_options[] = {
        {"file", required_argument, NULL, 'f'},
        {"check", no_argument,      NULL, 'c'},
        {"load", no_argument,      NULL, 'l'}
    };

    //循环执行，确保所有选项都能得到处理
    while(1) {
        int opt_index = 0;
        //参数解析方法，重点
        c = getopt_long(argc,
                        argv,
                        "cf:l",
                        long_options,
                        &opt_index);
        if(-1 == c) {
            break;
        }
        //根据返回值做出相应处理
        switch(c) {
        case 'c':
            cout << "check data" << endl;
            break;
        case 'f':
            cout << "file:" << optarg << endl;
            break;
        case 'l':
            cout << "load data!" << endl;
            break;
        default:
            cout << "???" << endl;
            break;
        }
    }
    return 0;
}



