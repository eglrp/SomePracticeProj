/*
给一个数组，返回它的最大连续子序列的和？(子向量的长度至少是1)
例如:{6,-3,-2,7,-15,1,2,2},
连续子向量的最大和为8(从第0个开始,到第3个为止)。
 */

#include <iostream>
#include <vector>

using namespace std;

int FindGreatestSumOfSubArray(vector<int> array) {
    int cursum = array[0];
    int maxsum = array[0];
    for(int i = 1; i < array.size(); i++) {
        cursum += array[i];
        if(cursum < array[i])  // 负正排列
            cursum = array[i];
        if(cursum > maxsum)  // 更新最大和
            maxsum = cursum;
    }
    return maxsum;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}