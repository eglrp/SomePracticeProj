/*
 * Author: Neverland_LY
 * Date: 2018-11-17
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
#include <mutex>
#include <fstream>

using namespace std;

/* Deferred Lock */
class LogFile {
    std::mutex _mu;
    ofstream _f;
public:
    LogFile() {
        _f.open("log.txt");
    }

    void shared_print(string id, int value) {
        std::lock_guard<mutex> locker(_mu);
        _f << "From " << id << ": " << value << endl;
    }

    // 这个只能锁一次
    void shared_print2(string id, int value) {
        //std::lock_guard<mutex> locker(_mu);
        std::unique_lock<mutex> locker(_mu);
        _f << "From " << id << ": " << value << endl;
        locker.unlock();
        // ....
    }

    // 可以随意 lock 和 unloick，重复好几次也可以
    // lock_guard做不到这一点
    //
    // 注意：lock_guard 和 unique-lock 不能被复制
    // 但是 unique_lock 可以 move，lock_guard 不可以move
    void shared_print3(string id, int value) {
        // std::defer_lock ，unique_lock 拥有 mutex 的所有权
        std::unique_lock<mutex> locker(_mu, std::defer_lock);

        // ...
        locker.lock();
        _f << "From " << id << ": " << value << endl;
        locker.unlock();

        // ...

        locker.lock();
        // ...
        locker.unlock();

        unique_lock<std::mutex> locker2 = std::move(locker);

        // 但是要注意，uniquelock 比 lockguard more heavyed
    }
};


class LogFile2 {
    std::mutex _mu;
    std::mutex _mu_open;
    ofstream _f;
public:
    LogFile2() {}

    void shared_print(string id, int value) {
        if( !_f.is_open()) { // 这样做线程是不安全的，因为两个线程可能同时打开这个文件，想想为什么？？？
            unique_lock<std::mutex> locker2(_mu_open);
            _f.open("log.txt"); // lazy initializer  or  upon first use EDM
        }

        // 正确做法是
        {
            unique_lock<std::mutex> locker2(_mu_open);
            if( !_f.is_open()) { // 这样就安全了，但是会引起另外一个问题
                _f.open("log.txt"); // lazy initializer  or  upon first use EDM
            }
            // 问题在于每次调用这个函数，都会进行锁的锁住与释放动作以及判断是否 open
            // 会有很大的资源开销
            //
            //
            // 这个问题的解决方法是用 sstd::once_flag，具体见下面的class3
        }
        std::lock_guard<mutex> locker(_mu);
        _f << "From " << id << ": " << value << endl;
    }
};


class LogFile3 {
    std::mutex _mu;
    std::once_flag _flag; // inportant
    ofstream _f;
public:
    LogFile3() {}

    void shared_print(string id, int value) {

        std::call_once(_flag, [&]() {
            _f.open("log.txt");
        });  // 这样能确保该语句只被执行一次且只被一个线程调用

        std::lock_guard<mutex> locker(_mu);
        _f << "From " << id << ": " << value << endl;
    }
};


int main(int argc, char *argv[]) {

    // Todo...


    cout << "Hello world!\n";

    return 0;
}