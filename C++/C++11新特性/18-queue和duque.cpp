/*
 * Author: Neverland_LY
 * Date: 2018-11-16
 * ProjectName: queue deque
 * Version: v-1.0
 *
 * Description: https://blog.csdn.net/qq_36238595/article/details/54905989
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <functional>

using namespace std;

class CLASSNAME {
public:
    CLASSNAME() {}
    ~CLASSNAME() {}
private:

};

int main(int argc, char *argv[]) {

    // queue
    {
        queue<int> q;
        //判断队列是否为空
        if (q.empty())  //为空时，返回true
            cout << "empty()" << endl;

        //入队
        for (int i = 0; i < 5; i++) {
            q.push(i);
        }

        cout << q.front() << endl;
        cout << q.back() << endl;
        cout << q.size() << endl;
        q.pop();
        cout << q.front() << endl;
    }

    // deque
    {
        deque<int> dq;
        if (dq.empty())
            cout << "empty()" << endl;
        for (int i = 1; i <= 5; i++)
            dq.push_back(i);  //将1-5从队尾入队

        for (int i = 6; i <= 10; i++)
            dq.push_front(i);  //将6-10从队头入队

        for (int i = 11; i <= 15; i++)
            dq.push_back(i);  //将6-10从队尾入队

        while (!dq.empty()) { //队列不为空
            cout << dq.front() << " "; //显示队头元素
            dq.pop_front();    //将队头元素弹出
        }
    }

    cout << "Hello world!\n";

    return 0;
}