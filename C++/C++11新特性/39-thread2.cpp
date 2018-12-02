/*
 * Author: Neverland_LY
 * Date: 2018-11-18
 * ProjectName: thread
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <exception>

using namespace std;

void test_thread1() {
    cout << "Beauty is only skin-deep!\n";
}

class Fctor1 {
public:
    void operator()() {
        for (int i = 0; i > -100; i--)
            cout << "from t1: " << i << endl;
    }
};

class Fctor2 {
public:
    void operator()(string msg) {
        cout << "it says: " << msg << endl;
    }
};

class Fctor3 {
public:
    void operator()(string &msg) {  // 加了个引用
        cout << "it says: " << msg << endl;

        msg = "Trust is the mother of deceit!";
    }
};


int main(int argc, char *argv[]) {

    {
        thread  t(test_thread1);
        t.join(); // 在 t 还没有 join 或者 detach 之前 test_thread() 就结束的话，程序会 terminate
    }

    {
        // 安全操作线程
        thread t(test_thread1); // 先定义
        try {
            cout << "from main thread: \n";
        } catch(...) {
            t.join(); // 这两个能保证总会执行 join
            throw(test_thread1);
        }
        t.join(); // 这两个能保证总会执行 join
    }

    {
        // RAII
        // wrap(t) 当 wrapper destroyed 的时候调用 join()
    }


    {
        // 调用仿函数
        Fctor1 f;
        thread t(f);

        try {
            cout << "from main thread: \n";
        } catch(...) {
            t.join(); // 这两个能保证总会执行 join
            throw(Fctor1());
        }
        t.join(); // 这两个能保证总会执行 join
    }

    {
        // 调用仿函数
        //
        // thread t(Fctor1()); // 这个编译不过去，原因是C++便准规定，当一个语句能被解释成函数时候，
        // 该语句优先被解释成函数，也就是说
        // 在这里 t 不再是线程，而是一个返回值为 thread 的函数，t 函数的参数是 一个 函数指针
        // 所以 t 作为函数名不能调用 join() 方法
        //
        //
        // 剞劂办法是再加一个括号，使其变为参数
        //
        thread t((Fctor1()));  // 这个是正确姿势

        try {
            cout << "from main thread: \n";
        } catch(...) {
            t.join(); // 这两个能保证总会执行 join
            throw(Fctor1());
        }
        t.join(); // 这两个能保证总会执行 join
    }


    {
        // 调用仿函数，传入值
        string msg("Where there is no trust, there is no love!\n");
        thread t((Fctor2()), msg);

        try {
            cout << "from main thread: " << msg << endl;
        } catch(...) {
            t.join(); // 这两个能保证总会执行 join
            throw(Fctor2());
        }
        t.join(); // 这两个能保证总会执行 join
    }

    {
        // 传入引用
        string msg("Where there is no trust, there is no love!\n");
        thread t((Fctor3()), std::ref(msg));  // 这里可以替换成指针(old pointer)

        t.join();
        cout << "from main thread: " << msg << endl;
    }

    {
        // std::move()
        string msg("Where there is no trust, there is no love!\n");
        thread t((Fctor2()), std::move(msg));  // s 在下面不可再用

        // thread t2 = t1; //error, 线程只可以 move 不可以 copy
        thread t2 = std::move(t); // 正解

        //打印线程
        cout << std::this_thread::get_id() << endl;
        cout << t.get_id() << endl;

        t.join();
        cout << "from main thread: " << msg << endl;
    }

    {
        // 线程不是越多越好
        std::thread::hardware_concurrency(); // 告诉我现在有多少线程可以供我使用
    }

    // Todo...


    cout << "Hello world!\n";

    return 0;
}