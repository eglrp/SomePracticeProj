/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: std::move()
 * Version: v-1.0
 *
 * Description: no
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class Complex {
public:
    Complex(int f)
        : _f(new float(f)) {
        cout << "Complex()" << endl;
    }
    Complex(const Complex &another)
        : _f(new float(*another._f)) {
        cout << "Complex(const Complex & another)" << endl;
    }
    Complex(Complex &&another)
        : _f(another._f) {
        another._f = nullptr;
        cout << " Complex(Complex && another)" << endl;
    }
    float *_f;
};

class Moveable {
public:
    Moveable(int i)
        : _i(new int(100)), _c(2.1) {}
    Moveable(const Moveable &another )
        : _i(new int(*another._i)), _c(another._c)
    {}
    Moveable(Moveable &&another)
        : _i(another._i), /*_c(std::move(another._c)) */_c(another._c) { // 精华在这里，但是好像没什么卵用
        another._i = nullptr;
    }
    ~Moveable() {
        if(_i != nullptr)
            delete _i;
    }
    int *_i;
    Complex _c;
};

int main(int argc, char *argv[]) {

    Moveable m(100);
    cout << *m._i << endl;

    cout << "-------\n";

    Moveable n(move(m));
    cout << *n._i << endl;


    cout << "Hello world!\n";

    return 0;
}