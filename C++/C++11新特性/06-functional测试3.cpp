/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: functional
 * Version: v-1.0
 *
 * Description: no
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class functor {
public:
    void operator()() {
        cout << __FUNCTION__ << endl;
    }
};

class A {
public:
    A(const function<void()> &cb): _callback(cb)
    {}
    void notify() {
        _callback();
    }
    function<void()> _callback;
};


void printWhenEven(int data, const function<void(int)> &f) {
    if(data % 2)
        f(data);
}

void print(int i) {
    cout << i << endl;
}


int main(int argc, char *argv[]) {

    functor fct;
    A a(fct);
    a.notify();


    for(int i = 0; i < 10; i++)
        // printWhenEven(i,print);
        printWhenEven(i, [](int i) {
        cout << i << endl;
    });

    cout << "Hello world!\n";

    return 0;
}