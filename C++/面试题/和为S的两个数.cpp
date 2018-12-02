/*
输入一个递增排序的数组和一个数字S，
在数组中查找两个数，使得他们的和正好是S，
如果有多对数字的和等于S，输出两个数的乘积最小的。
 */

#include <iostream>
#include <vector>

using namespace std;

vector<int> FindNumbersWithSum(vector<int> array, int sum) {
    vector<int> result;
    int length = array.size();
    if (length <= 1)
        return result;

    int i = 0;
    int j = length - 1;
    int Sum;

    while (i < j) {
        Sum = array[i] + array[j];
        if (Sum > sum)
            j--;
        else if (Sum < sum)
            i++;
        else {
            result.push_back(array[i]);  // 越靠近两端点，乘积越小
            result.push_back(array[j]);
            break;
        }
    }
    return result;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}