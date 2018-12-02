/*
汇编语言中有一种移位指令叫做循环左移（ROL），
现在有个简单的任务，就是用字符串模拟这个指令的运算结果。
对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。
例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。
 */

#include <iostream>
#include <string>

using namespace std;

string LeftRotateString(string str, int n) {
    if(n < 0)
        return NULL;
    if(n == 0)
        return str;

    string strTemp = ""; // 空字符串

    strTemp = str.substr(0, n);
    str.erase(0, n);
    str += strTemp;
    return str;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}