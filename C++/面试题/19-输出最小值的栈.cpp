/*
定义栈的数据结构，
请在该类型中实现一个能够得到栈中所含最小元素的min函数
（时间复杂度应为O（1））。
 */

#include <iostream>
#include <stack>

using namespace std;

class MyStack {
public:
    void push(int value) {
        StackInt.push(value);
        if(StackMin.empty())  // 注意逻辑
            StackMin.push(value);
        else if(StackMin.top() < value)
            StackMin.push(StackMin.top());
        else
            StackMin.push(value);
    }

    void pop() {
        if(!StackInt.empty()) {
            StackInt.pop();
            StackMin.pop();
        }
    }

    int top() {
        return StackInt.top();
    }
    int min() {
        return StackMin.top();
    }
private:
    stack<int> StackInt;
    stack<int> StackMin;
};

int main(int argc, char const *argv[]) {
    //Test
    /*
    eg：
    push ====================== >
    StackInt  11  9  6  20  18  2
    StackMin  11  9  6   6   6  2
    < ======================= pop
     */

    MyStack ms;
    int array[6] = {11, 9, 6, 20, 18, 2};
    for(int i = 0; i < sizeof(array) / sizeof(int); i++)
        ms.push(array[i]);


    for(int i = sizeof(array) / sizeof(int) - 1; i >= 0; i--) {
        cout << ms.min() << " ";
        ms.pop();
    }

    return 0;
}