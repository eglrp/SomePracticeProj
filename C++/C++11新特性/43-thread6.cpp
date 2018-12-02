/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: Condition Variable
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <deque>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

std::mutex mu;
std::deque<int> q;

std::condition_variable cond;

void function_1() {
    int count = 10;
    while (count > 0) {
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        cond.notify_one(); // notify one waiting thread, if there is one

        // cond.notify_all();

        std::this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

void function_2() { // 这是一个 busy waiting 的操作，inefficient
    int data = 0;
    while ( data != 1) {

        {
            std::unique_lock<mutex> locker(mu);
            if (!q.empty()) {
                data = q.back();
                q.pop_back();
                locker.unlock();
                cout << "t2 got a value from t1: " << data << endl;
            } else {
                locker.unlock();
                //解决办法一
                //问题是我们如何设置等待时间？？比如说下方的 10
                std::this_thread::sleep_for(chrono::milliseconds(10));
                //此时我们就需要 condition variable
            }

        }

        {
            //解决办法二
            std::unique_lock<mutex> locker(mu);
            cond.wait(locker); // put thread into sleep until being notify
            // 这句话发生了两件事情，unlock 然后再 sleep 等待唤醒，唤醒后重新锁定执行以下语句
            // 正因为要反复锁定解锁好几次，所以这里只能用 unique_lock 不能用 lock_guard
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout << "t2 got a value from t1: " << data << endl;

            // 注意：
            // 拥有 mutex 的线程不能 sleep ，既然 sleep 为什么要用 mutex
            //
            //
            // 注意：
            // 这样做又会引发新的问题，那就是该线程是一个 spurious weak ，他能自己唤醒自己

        }

        {
            //解决办法二
            std::unique_lock<mutex> locker(mu);
            cond.wait(locker, []() {
                return !q.empty(); // 就是说如果 q 是空的话，继续睡觉
            });
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout << "t2 got a value from t1: " << data << endl;
        }



    }
}

int main(int argc, char *argv[]) {

    {
        thread t1(function_1);
        thread t2(function_2);
        t1.join();
        t2.join();
    }


    cout << "Hello world!\n";

    return 0;
}