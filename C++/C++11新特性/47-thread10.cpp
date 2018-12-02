/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: Time Constrain
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

int foo(int N) {
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}

int main(int argc, char *argv[]) {

    // Summary

    /* Thread */
    std::thread t1(foo, 6);
    std::this_thread::sleep_for(chrono::milliseconds(3)); //毫秒
    std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::microseconds(4);
    std::this_thread::sleep_until(tp);

    /* Mutex */
    std::mutex mu;
    std::lock_guard<mutex> locker(mu);
    std::unique_lock<mutex> ulocker(mu);
    ulocker.try_lock();
    // ulocker.try_lock_for(std::chrono::nanoseconds(500)); // 微秒，到时后还没有锁定，程序就terminate了
    // ulocker.try_lock_until(tp);

    /* Condition Variable */
    std::condition_variable cond;
    cond.wait_for(ulocker, std::chrono::microseconds(2)); // 注意第一个参数是 ulocker
    cond.wait_until(ulocker, tp); // 注意第一个参数是 ulocker

    /* Future and Promise */
    std::promise<int> p;
    std::future<int> f = p.get_future();
    f.get();
    f.wait();
    f.wait_for(chrono::milliseconds(3));
    f.wait_until(tp);

    /* async */
    std::future<int> fu = std::async(std::launch::async, foo, 4); // foo 必须要有返回值，不然报错

    /* Packaged Task */
    std::packaged_task<int(int)> t(foo);
    std::future<int> fu2 = t.get_future();
    t(6);

    cout << "Hello world!\n";

    return 0;
}/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: Time Constrain
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

int foo(int N) {
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}

int main(int argc, char *argv[]) {

    // Summary

    /* Thread */
    std::thread t1(foo, 6);
    std::this_thread::sleep_for(chrono::milliseconds(3)); //毫秒
    std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::microseconds(4);
    std::this_thread::sleep_until(tp);

    /* Mutex */
    std::mutex mu;
    std::lock_guard<mutex> locker(mu);
    std::unique_lock<mutex> ulocker(mu);
    ulocker.try_lock();
    // ulocker.try_lock_for(std::chrono::nanoseconds(500)); // 微秒，到时后还没有锁定，程序就terminate了
    // ulocker.try_lock_until(tp);

    /* Condition Variable */
    std::condition_variable cond;
    cond.wait_for(ulocker, std::chrono::microseconds(2)); // 注意第一个参数是 ulocker
    cond.wait_until(ulocker, tp); // 注意第一个参数是 ulocker

    /* Future and Promise */
    std::promise<int> p;
    std::future<int> f = p.get_future();
    f.get();
    f.wait();
    f.wait_for(chrono::milliseconds(3));
    f.wait_until(tp);

    /* async */
    std::future<int> fu = std::async(std::launch::async, foo, 4); // foo 必须要有返回值，不然报错

    /* Packaged Task */
    std::packaged_task<int(int)> t(foo);
    std::future<int> fu2 = t.get_future();
    t(6);

    cout << "Hello world!\n";

    return 0;
}