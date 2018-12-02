/*
在一个长度为n的数组里的所有数字都在0到n-1的范围内。
数组中某些数字是重复的，但不知道有几个数字是重复的。
也不知道每个数字重复几次。请找出数组中任意一个重复的数字。
例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，
那么对应的输出是第一个重复的数字2。
 */

#include <iostream>

using namespace std;

bool duplicate(int *numbers, int length, int *duplication_number) {
    bool k[length]; // default false
    for (int i = 0; i < length; i++) {
        if (k[numbers[i]] == true) {
            *duplication_number = numbers[i];
            return true;
        }
        k[numbers[i]] = true;
    }
    return false;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}