/*
一只青蛙一次可以跳 1 级台阶，也可以跳上 2 级……它也可以跳 n 级
求该青蛙跳上一个 n 级的台阶总共有多少种跳法
 */

#include <iostream>

using namespace std;

int jumpFloorII(int number) {
    if(number == 0)
        return number;
    int total = 1;
    for(int i = 1; i < number; i++)
        total *= 2;
    return total;
}

int main(int argc, char const *argv[]) {
    //Test
    //eg: 跳三层方法有： 111 - 12 - 21 - 3
    cout << jumpFloorII(3) << endl;

    return 0;
}