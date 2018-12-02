/*
 * Author: Neverland_LY
 * Date: 2018-11-115
 * ProjectName: StaticAssert
 * Version: v-1.0
 *
 * Description: no
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

// 用于判断一个类是否为另一类的父类
template<typename D, typename B>
struct has_base {
    ~has_base() {
        cout << "~has_base()\n";
        void (*p)(D *, B *) = constraints;
    }
private:
    static void constraints(D *pd, B *pb) { // 这个函数永远不会被调用
        cout << "OK\n";
        pb = pd; // 子类能转化为父类，但是父类转化不为子类
    }
};

class CBase {};
class CDer : public CBase {};

// 静态断言的例子，用到了模版的全特化(函数只能全特化)
template<int n>
struct Factorial {
    static_assert(n <= 1, "n must bigger than 1");
    enum {value = n * Factorial < n - 1 >::value};
};

template<>
struct Factorial<0> {
    enum {value = 1};
};

int main(int argc, char *argv[]) {

    // Todo...
    has_base<CDer, CBase> a;
    // has_base<CBase, CDer> b; // 编译错误

    // 仿静态断言的例子
    int num = 3;
    // int arr[num > 15 ? num : -1];  // runtime error
    //
    // C++ 11 的静态断言
    //const int n = 3;
    //Factorial<n> f;
    //cout << f.value << endl; // 不会调用，哎


    cout << "Hello world!\n";

    return 0;
}