/*
在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。请完成一个函数，
输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
*/

#include <iostream>
#include <vector>

using namespace std;

bool Find(int target, const vector<vector<int> > &array) {
    if (array.empty())
        return false;

    if (target < array[0][0])
        return false;
    int _length = array.size();
    for (int i = 0; i < _length; i++) {
        if (array[i].empty())
            continue;
        else if(target >= array[i][0]) {  // 选定该行
            if (target <= array[i][array[i].size() - 1]) { // 是否小于该行的最后一个数字
                for (int j = array[i].size() - 1; j >= 0; j--) {
                    if (target == array[i][j])
                        return 1;
                    else if (target > array[i][j])
                        break;
                }
            } else {
                continue;
            }
        } else
            return false;
    }
    return false;
}


int main(int argc, char const *argv[]) {
    // Test
    vector<vector<int> > vec;
    for(int i = 0; i < 10; i++) {
        vector<int> vecson;
        for(int j = 0; j < 7; j++) {
            vecson.push_back(i + j);
            cout << i + j << "  ";
        }
        vec.push_back(vecson);
        cout << endl;
    }

    int target = 13;
    cout << "Is the target exist in array?  " <<
         ((Find(target, vec) == false) ? "False" : "True") << endl;

    return 0;
}