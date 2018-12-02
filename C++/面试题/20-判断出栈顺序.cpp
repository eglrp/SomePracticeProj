/*
输入两个整数序列，第一个序列表示栈的压入顺序，
请判断第二个序列是否可能为该栈的弹出顺序。
假设压入栈的所有数字均不相等。
例如序列1,2,3,4,5是某栈的压入顺序，
序列4,5,3,2,1是该压栈序列对应的一个弹出序列，
但4,3,5,1,2就不可能是该压栈序列的弹出序列。
（注意：这两个序列的长度是相等的）
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// 方法一
bool IsPopOrder1(vector<int> pushV, vector<int> popV) {
    if(pushV.size() == 0) return false;
    vector<int> v;
    for(int i = 0, j = 0 ; i < pushV.size();) {
        v.push_back(pushV[i++]);
        while(j < popV.size() && v.back() == popV[j]) {
            v.pop_back();
            j++;
        }
    }
    return v.empty();
}

// 方法二
bool IsPopOrder2(vector<int> pushV, vector<int> popV) {
    stack<int> st;//辅助栈
    int id = 0;
    for(int i = 0; i < popV.size(); ++i) {
        while(st.empty() || st.top() != popV[i]) {
            st.push(pushV[id++]);
            if(id > pushV.size()) {
                return false;
            }
        }
        st.pop();
    }

    if(st.empty()) // 判断条件就是最后有没有剩下的
        return true;
    else
        return false;
}

int main(int argc, char const *argv[]) {
    //Test
    vector<int> pushV;
    pushV.push_back(1); pushV.push_back(2); pushV.push_back(3);
    pushV.push_back(4); pushV.push_back(5);

    vector<int> popV;
    popV.push_back(4); popV.push_back(5); popV.push_back(1);
    popV.push_back(2); popV.push_back(3);

    cout << boolalpha << ((IsPopOrder1(pushV, popV) == 1) ? true : false) << endl;

    return 0;
}