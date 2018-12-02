/*
题目：n个数字（0,1,…,n-1）形成一个圆圈，从数字0开始，
每次从这个圆圈中删除第m个数字（第一个为当前数字本身，
第二个为当前数字的下一个数字）。当一个数字删除后，
从被删除数字的下一个继续删除第m个数字。
求出在这个圆圈中剩下的最后一个数字。
 */

/*
精讲：http://zhedahht.blog.163.com/blog/static/2541117420072250322938/
 */

#include <iostream>

using namespace std;

//f[i]=(f[i-1]+m)%i;  (i>1) 这个递推公式的循环实现版

int LastRemaining1(int n, int m) {
    if(n == 0)
        return -1;

    int s = 0;
    for(int i = 2; i <= n; i++) {
        s = (s + m) % i;
    }
    return s;
}

int LastRemaining2(unsigned int n, unsigned int m) {
    if(n == 0)
        return -1;
    if(n == 1)
        return 0;
    else
        return (LastRemaining2(n - 1, m) + m) % n;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}