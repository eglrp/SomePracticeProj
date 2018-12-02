/*
给定一个double类型的浮点数base和int类型的整数exponent。
求base的exponent次方。
 */

#include <iostream>

using namespace std;

double Power(double base, int exponent) {
    if(exponent > 0) {
        if(exponent == 1)
            return base;
        if(exponent % 2 == 0)
            return Power(base, exponent / 2) * Power(base, exponent / 2);
        else
            return Power(base, exponent / 2) * Power(base, exponent / 2 + 1);
    } else if (exponent == 0) {
        return 1;
    } else {
        return 1 / Power(base, 0 - exponent);
    }
}

int main(int argc, char const *argv[]) {
    //Test
    double PI = 3.1415926;
    cout << Power(PI, 0) << endl;
    cout << Power(PI, 1) << endl;
    cout << Power(PI, 2) << endl;
    return 0;
}