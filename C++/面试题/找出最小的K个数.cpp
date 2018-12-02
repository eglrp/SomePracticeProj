/*
输入n个整数，找出其中最小的K个数。
例如输入4,5,1,6,2,7,3,8这8个数字，
则最小的4个数字是1,2,3,4。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> GetLeastNumber1(vector<int> input, int k) {
    vector<int> res;
    if(input.empty() || k > input.size())
        return res;

    sort(input.begin(), input.end());

    for(int i = 0; i < k; i++)
        res.push_back(input[i]);

    return res;
}

//multiset集合  利用仿函数改变排序顺序 时间复杂度O（nlogk）
vector<int> GetLeastNumbers2(vector<int> input, int k) {
    int len = input.size();
    if(len <= 0 || k > len) return vector<int>();

    //仿函数中的greater<T>模板，从大到小排序
    multiset<int, greater<int> > leastNums;
    vector<int>::iterator vec_it = input.begin();
    for(; vec_it != input.end(); vec_it++) {
        //将前k个元素插入集合
        if(leastNums.size() < k)
            leastNums.insert(*vec_it);
        else {
            //第一个元素是最大值
            multiset<int, greater<int> >::iterator greatest_it = leastNums.begin();
            //如果后续元素<第一个元素，删除第一个，加入当前元素
            if(*vec_it < * (leastNums.begin())) {
                leastNums.erase(greatest_it);
                leastNums.insert(*vec_it);
            }
        }
    }

    return vector<int>(leastNums.begin(), leastNums.end());
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}