/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: mutex
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <stdlib.h>
#include <vector>

using namespace std;

mutex gLock; // 锁

void test_lock() {
    gLock.lock();
    cout << "enter thread " << this_thread::get_id() << endl;

    this_thread::sleep_for(chrono::seconds(rand() % 10));

    cout << "leave thread " << this_thread::get_id() << endl;
    gLock.unlock();
}



mutex g_mutex; // 全局锁

void test_lock_guard() {
    lock_guard<mutex> lock(g_mutex);
    cout << "enter thread " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::seconds(rand() % 10));
    cout << "leave thread " << this_thread::get_id() << endl;
}



recursive_mutex g_rmtx; // 递归锁

int factorial(int n) {
    // lock_guard<mutex> lock(g_mtx);
    lock_guard<recursive_mutex> lock(g_rmtx);
    if(n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}



// 线程安全的 vector
template <typename T>
class containter {
public:
    void add(T t);
    void del(T t);
    void dump();
private:
    mutex _lock;
    vector<T> _elements;
};


template <typename T>
void containter<T>::add(T t) {
    _lock.lock();
    _elements.push_back(t);
    _lock.unlock();
}

template <typename T>
void containter<T>::del(T t) {
    _lock.lock();
    auto itr = find(_elements.first(), _elements.second(), t);
    if(itr != _elements.end())
        _elements.erase(itr);
    _lock.unlock();
}

template <typename T>
void containter<T>::dump() {
    _lock.lock();
    for(auto &i : _elements) {
        cout << i << endl;
    }
    _lock.unlock();
}

containter<int> ci;

void func() {
    ci.add(rand() % 100);
}

int main(int argc, char *argv[]) {

    {
        cout << "main thread " << this_thread::get_id() << endl;

        srand(time(NULL));
        thread t1(test_lock);
        thread t2(test_lock);
        thread t3(test_lock);
        t3.join();
        t2.join();
        t1.join();  // 顺序不是固定的
    }

    cout << "----------\n";

    {
        cout << "main thread " << this_thread::get_id() << endl;

        srand(time(NULL));
        thread t1(test_lock_guard);
        thread t2(test_lock_guard);
        thread t3(test_lock_guard);
        t1.join();
        t2.join();
        t3.join();  // 顺序依次执行
    }

    cout << "----------\n";

    {
        cout << "main thread " << this_thread::get_id() << endl;

        cout << "5! = " << factorial(5) << endl;
    }

    cout << "----------\n";

    {
        // std::timed_mutex
        // 带超时的互斥锁，在等待互斥锁的进候，
        // 不知道获取锁需要多久，为了不至于一直
        // 在等待，就设置一个超时时间。在超时后，
        // 还可以去处理其它的事情。
    }

    {
        cout << "main thread " << this_thread::get_id() << endl;

        srand(time(NULL));
        thread t1(func);
        thread t2(func);
        thread t3(func);
        t1.join();
        t2.join();
        t3.join();
        ci.dump();
    }


    return 0;
}