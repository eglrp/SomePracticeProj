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

using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <fstream>

#include <mutex>

using namespace std;

class LogFile { //RAII
    std::mutex mu1;
    std::mutex mu2;
    ofstream _f;
public:
    LogFile() {
        _f.open("log.txt");
    }// Need destructor to close file

    void shared_print1(string id, int value) {
        std::lock_guard<std::mutex> locker1(mu1);
        std::lock_guard<std::mutex> locker2(mu2);
        cout << "From :" << id << ": " << value << endl;
    }

    //死锁
    void shared_print2(string id, int value) {
        std::lock_guard<std::mutex> locker2(mu2);
        / std::lock_guard<std::mutex> locker1(mu1);
        cout << "From :" << id << ": " << value << endl;
    }
    // 解决办法一：调整顺序
    void shared_print3(string id, int value) {
        std::lock_guard<std::mutex> locker1(mu1);
        std::lock_guard<std::mutex> locker2(mu2);
        // std::lock_guard<std::mutex> locker1(mu1);
        cout << "From :" << id << ": " << value << endl;
    }

    // 解决办法二：std::adopt_lock
    void shared_print4(string id, int value) {
        std::lock(mu1, mu2);
        std::lock_guard<std::mutex> locker1(mu1, std::adopt_lock);
        std::lock_guard<std::mutex> locker2(mu2, std::adopt_lock);
        // std::lock_guard<std::mutex> locker1(mu1);
        cout << "From :" << id << ": " << value << endl;
    }

    // 现实生活中注意：
    // 1. 你是否需要使用两个 mutex
    // 2. 尽量不要用自己定义的函数调用 mutex
    // 3. 尽量使用 std::lock()
    // 4. lock the mutex in same order
    //
    //
    //
    //
    /* Avoiding deadlock
    1. Prefer locking single mutex.
    2. Avoid locking a mutex and then calling a user provided function.
    3. Use std::lock() to lock more than one mutex.
    4. Lock the mutex in same order.


    Locking Granularity:
    - Fine-grained lock:  protects small amount of data
    - Coarse-grained lock: protects big amount of data
    */
};

void test_thread1(LogFile &log) {
    for (int i = 0; i >= -50 ; i--)
        log.shared_print1("t1:", i);
}

int main(int argc, char *argv[]) {
    // {
    //     LogFile log;
    //     thread t(test_thread1, std::ref(log));
    //     for (int i = 0; i < 50; i++)
    //         log.shared_print1(string("From main: "), i);

    //     t.join();
    // }

    {
        // dead lock
        LogFile log;
        thread t(test_thread1, std::ref(log));
        for (int i = 0; i < 50; i++)
            log.shared_print2(string("From main: "), i);

        t.join();

        // 为了不发生死锁，所以一定要注意保证锁的先后顺序一致
    }

    cout << "Hello world!\n";

    return 0;
}