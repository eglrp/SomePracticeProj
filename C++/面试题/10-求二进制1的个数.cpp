/*
输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
 */

#include <iostream>

using namespace std;

int NumberOf1(int n) {
    int count = 0;
    unsigned int flag = 1;
    while(flag) {
        if (n & flag) {
            count++;
        }
        flag = flag << 1;
    }
    return count;
}

int main(int argc, char const *argv[]) {
    //Test
    int m = 10;  // 1010
    cout << NumberOf1(m) << endl;
    int n = 11;  // 1011
    cout << NumberOf1(n) << endl;
    int p = 12;  // 1100
    cout << NumberOf1(p) << endl;
    return 0;
}
