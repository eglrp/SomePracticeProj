/*
一个整型数组里除了两个数字之外，其他的数字都出现了偶数次。
请写程序找出这两个只出现一次的数字。
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void FindNumsAppearOnce(vector<int> data, int *num1, int *num2) {
        if(data.size() < 2)
            return;

        int resultExclusiveOR = 0;
        for(int i = 0; i < data.size(); i++) {
            resultExclusiveOR ^= data[i];
        }

        unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);

        *num1 = *num2 = 0;
        for(int j = 0; j < data.size(); j++) {
            if(IsBit1(data[j], indexOf1))
                *num1 ^= data[j];
            else
                *num2 ^= data[j];
        }
    }

    unsigned int FindFirstBitIs1(int num) {
        int indexBit = 0;
        while(((num & 1) == 0) && (indexBit < 8 * sizeof(int))) {
            num = num >> 1;
            indexBit++;
        }
        return indexBit;
    }

    bool IsBit1(int num, unsigned int indexBit) {
        num = num >> indexBit;
        return (num & 1);
    }
};

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}