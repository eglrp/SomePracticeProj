/*
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minNumberInRotateArray1(vector<int> rotateArray) {
    sort(rotateArray.begin(), rotateArray.end());
    return rotateArray[0];
}

int minNumberInRotateArray2(vector<int> array) {
    int low = 0 ;
    int high = array.size() - 1;
    while(low < high) {
        int mid = low + (high - low) / 2;
        if(array[mid] > array[high]) {
            low = mid + 1;
        } else if(array[mid] == array[high]) {  //这步是关键
            high = high - 1;
        } else {
            high = mid;
        }
    }
    return array[low];
}

int main(int argc, char const *argv[]) {
    //Test
    std::vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(1);
    v.push_back(2);

    cout << minNumberInRotateArray1(v) << endl;
    cout << minNumberInRotateArray2(v) << endl;

    return 0;
}