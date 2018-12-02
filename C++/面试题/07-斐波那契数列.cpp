/*
输出斐波那契数列的第 n 项(从0开始，第0项为0)
斐波那契数列：0 1 1 2 3 5 8 13 ...
 */

#include <iostream>

using namespace std;

// 方法一
int Fibonacci1(int n) {
    if(n == 0)
        return 0;

    if(n == 1)
        return 1;

    int a = 0, b = 1;
    int m = 0;
    int i;

    for(i = 2; i <= n; i++) {  // a + b = m
        m = a + b;
        a = b;
        b = m;
    }
    return m;
}

// 方法二
int Fibonacci2(int n) {
    int result[3] = {0, 1, 1};
    if (n <= 2)
        return result[n];
    return Fibonacci2(n - 1) + Fibonacci2(n - 2);
}

int main(int argc, char const *argv[]) {
    // Test
    for(int i = 0; i < 20; i++)  // 从 1 开始
        cout << Fibonacci1(i) << " ";

    cout << "\n-----------------\n";

    for(int i = 0; i < 20; i++)  // 从 0 开始
        cout << Fibonacci2(i) << " ";

    return 0;
}