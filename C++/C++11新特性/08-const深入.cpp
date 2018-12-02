#include <iostream>
#include <string>

using namespace std;

// 注意点1：不会影响不同文件的编译连接
const int global_var = 100; // 只在该文件可见，所以另一个文件定义 const global_var = 200;不影像

//注意点2：会影响重写
class A {
public:
    virtual int foo() const {
        return 100;
    }
};

class B : public A {
public:
    virtual int foo() {
        return 1;
    }
};

//注意点3：影响重载
class C1 {
public:
    int foo() {}
    // const int foo(){} 不是重载
};

class C2 {
public:
    int foo() {}
    int foo() const {} // 重载
};

class C3 {
public:
    int foo(int) {}
    // int foo(const int){} // 不是重载
};

class C4 {
public:
    int foo(int) {}
    int foo(const int &) {}
};

class C5 {
public:
    int foo(int) {}
    int foo(int &) {} // 重载
};

//注意点4：“浅”const
class D {
public:
    void bar() const {
        *ptr = 666;
        // ptr = 0x0012;
    }

private:
    int *ptr;
};

int main(int argc, char const *argv[]) {

    A *ptr = new B;
    cout << ptr->foo() << endl; //输出100

    return 0;
}