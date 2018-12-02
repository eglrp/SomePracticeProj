/*
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，
并保证奇数和奇数，偶数和偶数之间的相对位置不变。
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void reOrderArray1(vector<int> &array) {
    for (int i = 0; i < array.size(); i++) {
        for (int j = array.size() - 1; j > i; j--) {
            if (array[j] % 2 == 1 && array[j - 1] % 2 == 0) { //前偶后奇交换
                swap(array[j], array[j - 1]);
            }
        }
    }
}

void reOrderArray2(vector<int> &array) {

    vector<int> array_temp;
    vector<int>::iterator ib1, ie1;
    ib1 = array.begin();


    for (; ib1 != array.end();) { //遇见偶数，就保存到新数组，同时从原数组中删除
        if (*ib1 % 2 == 0) {
            array_temp.push_back(*ib1);
            ib1 = array.erase(ib1);
        } else {
            ib1++;
        }

    }
    vector<int>::iterator ib2, ie2;
    ib2 = array_temp.begin();
    ie2 = array_temp.end();

    for (; ib2 != ie2; ib2++) {           //将新数组的数添加到老数组
        array.push_back(*ib2);
    }
}

//奇数返回真
bool isOk(int n) {
    return ((n & 1) == 1);
}

void reOrderArray3(vector<int> &array) {
    //用的STL　stable_partition 这个函数
    stable_partition(array.begin(), array.end(), isOk);
}

int main(int argc, char const *argv[]) {
    //Test
    int array[8] = {1, 8, 2, 3, 7, 5, 6, 4};
    cout << "初始向量:\n18237564\n------\n";
    vector<int> vec1(array, array + 8);
    vector<int> vec2(array, array + 8);
    vector<int> vec3(array, array + 8);

    reOrderArray1(vec1);
    reOrderArray2(vec2);
    reOrderArray3(vec3);

    vector<int>::iterator it1 = vec1.begin();
    for(; it1 != vec1.end(); it1++)
        cout << *it1;

    cout << "\n------\n";

    vector<int>::iterator it2 = vec2.begin();
    for(; it2 != vec2.end(); it2++)
        cout << *it2;

    cout << "\n------\n";

    vector<int>::iterator it3 = vec3.begin();
    for(; it3 != vec3.end(); it3++)
        cout << *it3;

    return 0;
}
