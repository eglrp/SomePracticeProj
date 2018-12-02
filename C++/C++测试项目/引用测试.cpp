#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int a = 1;
    int &b = a;
    int &c = b;
    // int &&c = a; //没有引用的引用
    int d = 10, e = 20;
    int &dd = d;
    int &ee = e;
    dd = ee;
    cout << dd <<ee<<endl;
    return 0;
}