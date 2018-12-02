/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: Using Callable Objects
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

// C++11 / 14
#include <functional>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <condition_variable>

using namespace std;

/* async() are used in the same ways as thread(), bind() */


class A {
public:
    string note;
    void f(int x, char c) {}

    int operator()(int N) {
        return 0;
    }
};


void foo(int x) {}

int main() {

    {
        A a;
        // 几种常见的线程调用方法
        std::thread t1(a, 6); // 注意这个写法
        std::async(std::launch::async, a, 6);
        std::bind(a, 6);
        // std::call_once(once_flag, a, 6);
    }

    {
        A a;
        std::thread t1(a, 6); // copy_of_a() in a different thread
        std::thread t2(std::ref(a), 6); // a() in a different thread
        std::thread t22(std::move(a), 6); // a is no longer usable in main thread
        std::thread t3(A(), 6); // move temp A in a different thread
        std::thread t4([](int x) {
            return x * x;
        }, 6); // lambda func
        std::thread t5(foo, 6); // func
        std::thread t6(&A::f, a, 8, 'w'); // copy_of_a.f(8, 'w') in  a different thread
        std::thread t7(&A::f, &a, 8, 'w'); // a.f(8, 'w') in  a different thread
    }

    return 0;
}

