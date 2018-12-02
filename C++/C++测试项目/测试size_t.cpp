#include <stdio.h>
#include <iostream>


using namespace std;

long double operator"" _cm(long double x) {
    return x * 10;
}

long double operator"" _m(long double x) {
    return x * 1000;
}
long double operator"" _mm(long double x) {
    return x ;
}

int main(int argc, char const *argv[]) {
    long double height = 3.4_cm;

    cout << height;
    return 0;
}