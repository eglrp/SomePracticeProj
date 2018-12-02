/*
 * Author: Neverland_LY
 * Date: 2018-11-18
 * ProjectName: thread
 * Version: v-1.0
 *
 * Description: no
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <fstream>

#include <mutex>

using namespace std;

std::mutex mu;

void test_thread1() {
    cout << "Beauty is only skin-deep!\n";
}

void shared_print(string msg, int id) {
    mu.lock();
    cout << msg << id << endl; // 这个发生异常怎么办？那么 mu 永远不会被释放
    mu.unlock();
}

void shared_print2(string msg, int id) {
    std::lock_guard<std::mutex> guard(mu); // RAII
    cout << msg << id << endl; //但是这样做还有一个问题，因为cout是全局资源
    // 其他对象想用 cout 的时候不必经过 mutex
    // 更安全的做法见下面的 LogFile class
}

class LogFile { //RAII
    std::mutex m_mutex;
    ofstream f;
public:
    LogFile() {
        f.open("log.txt");
    }// Need destructor to close file

    void shared_print(string id, int value) {
        std::lock_guard<std::mutex> locker(m_mutex);
        f << "From :" << id << ":" << value << endl;
    }

    // Never return f to outside world
    // ofstream & getStream() {return f;} // bad idea
    // Never pass f as an argument to user provided function
    // void processf(void fun(ofstream&)){fun(f);}
};

void test_thread2() {
    for (int i = 10; i >= 0 ; i--)
        shared_print(string("Beauty is only skin-deep!"), i);
}

void test_thread3(LogFile &log) {
    for (int i = 10; i >= 0 ; i--)
        log.shared_print(string("Beauty is only skin-deep!"), i);
}


// 特例
class stack {
    int *_data;
    std::mutex _mu;
public:
    void pop(); //
    int &top();
}

void foo(stack &st) {
    int v = st.pop();
    // process(v); 处理一些复杂的事情
    // 在这里 加入有两个线程同时处理 v，就可能发生问题
    //
    // 正确做法是返回一个引用
    // int &pop();
    // 但是这样又会引发新问题，那就是 exception，
    // 所以标准库也是用的
}

int main(int argc, char *argv[]) {

    {
        // print mess up, 因为他们在竞争 cout 这个资源
        thread t(test_thread1); // 先定义

        for (int i = 10; i >= 0 ; i--)
            cout << "from main: \n";

        t.join();
    }

    cout << "----------\n";

    {
        thread t(test_thread2); // 先定义

        for (int i = 10; i >= 0 ; i--)
            shared_print(string("Beauty is only skin-deep!"), i);

        t.join();
    }

    cout << "---------\n";

    {
        // 这样做就会很安全了
        LogFile log;
        thread t(test_thread3, std::ref(log));
        for (int i = 10; i >= 0 ; i--)
            log.shared_print(string("Beauty is only skin-deep!"), i);

        t.join();
    }




    cout << "Hello world!\n";

    return 0;
}