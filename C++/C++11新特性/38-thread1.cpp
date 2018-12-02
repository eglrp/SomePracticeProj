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
#include <unistd.h>

using namespace std;

void func1() {
    cout << "thread id:" << this_thread::get_id() << endl;
    cout << "do some work" << endl;
    sleep(3);
    cout << "finished" << endl;
}

void func2(int n, string s) {
    for(int i = 0; i < n ; i++) {
        cout << s << endl;
    }
}

void func3(int &n, string &s) {
    for(int i = 0; i < n ; i++) {
        cout << s << endl;
    }
    n = 10;
    s = "america";
}

int main(int argc, char *argv[]) {

    {

        // t.join 和 t.detach 标志着，线程对象和线程的关系
        // t.join == 线程与线程对象的同步关系。
        // t.detach == 线程与线程对象的异步关系。
        //
        // detach 后的线程，不能再 join，是否可以 join 可以通过 joinable 来判断
        // if(t.joinable())
        //     t.join();

        cout << "main thread id:" << this_thread::get_id() << endl;
        thread t(func1);
        t.join();
    }

    {
        //线程，有自己独立的栈。可以共享全局的变量。
        //在线程启动的时候可以传入启动参数。
        thread t(func2, 5, "China");
        t.join();
    }

    {
        // 除了传入参数，共享全局以外，还可以传入本地变量的引用。
        // 以下传递引用的方式，编译通不过。
        int n = 5;
        string s = "China";
        // thread t(func,n, s); // error
        thread t(func3, std::ref(n), std::ref(s));
        cout << "n = " << n << endl;
        cout << "s = " << s << endl;
        t.join();
    }




    cout << "Hello world!\n";

    return 0;
}