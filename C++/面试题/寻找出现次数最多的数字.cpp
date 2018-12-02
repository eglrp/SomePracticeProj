/*
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。
由于数字2在数组中出现了5次，
超过数组长度的一半，因此输出2。如果不存在则输出0。
 */

#include <iostream>

using namespace std;

int findMoreThanHalfNum(int array[], int size) {
    if(size == 0)
        return -1;
    int result = array[0];
    int count = 1;
    for(int i = 1; i < size; i++) {
        if(array[i] == result) {
            count++;
        } else {
            if(count == 0) {
                result = array[i];
                count++;
            } else
                count--;
        }
    }

    if(count != 0)
        return result;
    else
        return -1;
}

int main(int argc, char const *argv[]) {
    //Test
    int array[] = {1, 2, 2, 3, 3, 3, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6};
    cout << findMoreThanHalfNum(array, sizeof(array) / sizeof(array[0])) << endl;

    return 0;
}