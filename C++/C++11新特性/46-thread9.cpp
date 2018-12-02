/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: packaged_task
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <deque>

// C++11 / 14
#include <functional>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <condition_variable>

using namespace std;

int factorial(int N) {
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;

    return res;
}


std::deque<std::packaged_task<int()>> task_q;

vois thread1() {
    std::packaged_task<int()> t;
    t = std::move(task_q.front());
    t();
}

std::mutex mu;
std::condition_variable cond;

vois thread2() {
    std::packaged_task<int()> t;
    {
        // std::lock_guard<std::mutex> locker(mu);
        std::unique_lock<std::mutex> locker(mu);
        conde.wait(locker, []() {
            return !task_q.empty();
        });
        t = std::move(task_q.front()); // 如果 task_q 是空的话很危险
        task_q.pop_front();
    }

    t();
}

int main(int argc, char *argv[]) {

    {
        std::thread t1(factorial, 6); // 带有参数
        std::packaged_task<int(int)> t(factorial); // 注意这里没有参数

        /// ...

        t(6); // In a different context

        // int x = t(6); // err, t always return void

        // 正确做法
        int x = t.get_future().get();

    }


    {
        // 注意这个 int 不再有参数 int
        std::packaged_task<int()> t(std::bind(factorial, 6)); // 但是可以这样绑定
        // 这样做的坏处是：之后不能再改变参数，因为已经是 unbindable

        /// ...

        t(); // 这里也没有参数了
    }

    {
        // 思考：我们真的需要 std::packaged_task 吗？
        // std::packaged_task<int()> t(std::bind(factorial, 6));
        //
        auto f = std::bind(factorial, 6);
        f(); // 这样也能实现功能，但是为什么需要 packaged_task
    }

    {
        std::thread t1(thread1);
        std::packaged_task<int()> t(std::bind(factorial, 6));
        std::future<int> fu = t.get_future();
        task_q.push_back(t);

        cout << fu.get(); // 获得子线程的值

        t1.join();

        // 注意这个代码有危险
        // 因为此时 task_q 属于main线程和子线程的竞争资源，所以要用mutex
        //
        //
        // 正确做法见下面
    }


    {
        std::thread t1(thread2);
        std::packaged_task<int()> t(std::bind(factorial, 6));
        std::future<int> fu = t.get_future();
        {
            // 这里 lock_guard 和 unique_lock 都可以
            std::lock_guard<std::mutex> locker(mu);
            task_q.push_back(std::move(t)); // 注意这里(如果程序之后不再用 t 的话)
        }
        cond.notify_one();

        cout << fu.get(); // 获得子线程的值
        t1.join();
    }



    /* Summary
     * 3 ways to get a future:
     * - promise::get_future()
     * - packaged_task::get_future()
     * - async() returns a future
     */




    cout << "Hello world!\n";

    return 0;
}