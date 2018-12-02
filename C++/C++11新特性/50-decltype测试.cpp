#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

auto foo() {
    return 0;
}

int main() {
z
    static_assert(std::is_same<decltype(foo()), int>(), "123");

    return 0;
}

// 更多详细请看我的博客
// https://blog.csdn.net/qq_34719188/article/details/84070074


