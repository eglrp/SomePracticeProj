/*
 * Author: Neverland_LY
 * Date: 2018-11-15
 * ProjectName: NewTest
 * Version: v-1.0
 *
 * Description: https://www.cnblogs.com/lca1826/p/6506183.html
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

int main(int argc, char *argv[]) {

    // 基本用法
    int *x = new int;       //开辟一个存放整数的存储空间，返回一个指向该存储空间的地址(即指针)
    int *a = new int(100);  //开辟一个存放整数的空间，并指定该整数的初值为100，返回一个指向该存储空间的地址
    char *b = new char[10]; //开辟一个存放字符数组(包括10个元素)的空间，返回首元素的地址
    float *p = new float (3.14159); //开辟一个存放单精度数的空间，并指定该实数的初值为//3.14159，将返回的该空间的地址赋给指针变量p

    delete x, a, b, p;

    // 动态申请列大小固定的二维数组
    int row = 2;
    int col = 3;
    //申请一维数据并将其转成二维数组指针
    int *pp_arr = new int[row * col];
    int (*pp)[col] = (int(*)[col])pp_arr;
    delete pp_arr, pp;

    // 动态申请大小不固定的二维数组
    cin >> row >> col;
    int **ppp = new int *[row];
    for (int i = 0; i < row; i ++) {
        ppp[i] = new int[col];
    }
    delete ppp;


    cout << "Hello world!\n";

    return 0;
}