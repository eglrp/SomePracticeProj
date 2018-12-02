/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: Condition Variable
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::mutex mtx;
std::condition_variable cv;

bool ready = false;

void print_id (int id) {
    std::unique_lock<std::mutex> lck(mtx);
    if (!ready)
        cv.wait(lck);
    // ...
    std::cout << "thread " << id << " threadID: " << this_thread::get_id() << '\n';
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

int main () {
    std::thread threads[10];
    cout << "spawn 10 threads: \n";
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(print_id, i);
    std::cout << "10 threads ready to race...\n";

    go(); // go!

    for (auto &th : threads) {
        // cout << "add thread\n";
        th.join();
    }

    return 0;
}