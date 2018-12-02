/*

 */

#include <iostream>

using namespace std;

// n(n+1)/2
int Sum1(int n) {
    bool a[n][n + 1];
    return sizeof(a) >> 1;
}

//解题思路：
//1.需利用逻辑与的短路特性实现递归终止。 
//2.当n==0时，(n>0)&&((sum+=Sum(n-1))>0)只执行前面的判断，为false，然后直接返回0；
//3.当n>0时，执行sum+=Sum(n-1)，实现递归计算Sum(n)。
int Sum2(int n) {
    int sum = n;
    bool ans = (n > 0) && ((sum += Sum2(n - 1)) > 0);
    return sum;
}

int main(int argc, char const *argv[]) {
    /* code */
    bool b;
    cout << boolalpha << b;
    return 0;
}