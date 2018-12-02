/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: chrono
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]) {
    chrono::duration<double, ratio<1, 1000>> millisecond(10);
    chrono::hours h(10);
    chrono::minutes min(10);
    chrono::seconds sec(10);
    chrono::milliseconds millis(10);
    chrono::microseconds micros(10);
    chrono::nanoseconds nanos(10);
    this_thread::sleep_for(sec);
    this_thread::sleep_for(chrono::seconds(10));

    cout << "Hello UNIX TIME\n";

    return 0;
}