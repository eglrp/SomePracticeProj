/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: rvalue rvalue
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

#if 0
int &foo() {
    int i = 1;
    return i; // warning: reference to local variable 'i' returned [-Wreturn-local-addr]
}

int bar() {
    int i = 1;
    return &i; // warning: address of local variable 'i' returned [-Wreturn-local-addr]
}

#endif

class A {
public:
    A() {}
    dis() {
        cout << "This is dis()\n";
    }
};

A createA() {
    return A();
}

class Copyable {
public:
    Copyable() {}
    Copyable(const Copyable &) {
        cout << "Copyable" << endl;
    }
};

Copyable getCopyable() {
    return Copyable();
}

void acceptValue(Copyable o) {}

// error: invalid initialization of non-const reference of type 'Copyable&' from an rvalue of type 'Copyable'
// void acceptRef(Copyable &o) {}

void acceptRef(const Copyable &o) {}

void accetpRRef(Copyable &&o) {}

int main(int argc, char *argv[]) {

    int a;
    int &lref = a;
    //int &&rref = a; //error: cannot bind 'int' lvalue to 'int&&'
    // int &elref = a * 34; // error: invalid initialization of non-const reference of type 'int&' from an rvalue of type 'int'
    const int &eclref = a * 34;
    int &&erref = a * 34;

    // A& obja = createA(); // error: invalid initialization of non-const reference of type 'A&' from an rvalue of type 'A'
    A &&obja = createA();

    {
        // int& ri = 5; // error: invalid initialization of non-const reference of type 'int&' from an rvalue of type 'int'
        const &cri = 5;
        float f = 34.5;
        // int & irf = f; // error: invalid initialization of non-const reference of type 'int&' from an rvalue of type 'int'
        const int &cirf = f;
        A objA;
        // int& irA = objA; // error: invalid initialization of reference of type 'int&' from expression of type 'A'
        // const int& cirA = objA; // error: invalid initialization of reference of type 'const int&' from expression of type 'A'

        const A &ret = createA();
        // ret.dis(); // error: passing 'const A' as 'this' argument discards qualifiers [-fpermissive]

        A &&ret2 = createA();  // correct
        ret2.dis();
    }

    {
        acceptValue(getCopyable());
        acceptRef(getCopyable());
        accetpRRef(getCopyable());
    }

    cout << "Hello world!\n";

    return 0;
}

/*
左值引用于右值引用的对比
    都属于引用类型。
  都必须初始化。左值引用是具名变量值的别名，右值引用是匿名变量的别名。
  左值引用，用于传参，好处在于，扩展对象的作用域。则右值引用的作用就在于延长了临时对象的生命周期。
  避免“先拷贝再废弃”带来的性能浪费。
  对将亡值进行引用的类型；它存在的目的就是为了实现移动语义。
 */