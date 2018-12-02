/*
一只青蛙一次可以跳 1 级台阶，也可以跳 2 级。
求该青蛙跳上一个 n 级台阶总共有多少种跳法(先后次序不同算不同的结果)。
 */

#include <iostream>

using namespace std;

// 方法一
// 和上面的斐波那契数列一样

// 方法二
int jumpFloor(int n) {
    int f = 1, g = 2;
    n--;
    while(n--) {
        g += f;
        f = g - f;
    }
    return f;
}

int main(int argc, char const *argv[]) {
    //Test
    //eg: 跳三层方法有： 111 - 12 - 21
    cout << jumpFloor(3) << endl;
    //eg: 跳五层方法有： 1111 - 121 - 112 - 211 - 22
    cout << jumpFloor(4) << endl;

    return 0;
}