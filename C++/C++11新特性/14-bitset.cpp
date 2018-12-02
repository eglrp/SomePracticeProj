/*
 * Author: Neverland_LY
 * Date: 2018-11-16
 * ProjectName: bitset
 * Version: v-1.0
 *
 * Description: https://www.cnblogs.com/RabbitHu/p/bitset.html
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <bitset>

using namespace std;

class CLASSNAME {
public:
    CLASSNAME() {}
    ~CLASSNAME() {}
private:

};

int main(int argc, char *argv[]) {

    // Basic...
    {
        std::bitset<16> foo;
        std::bitset<16> bar (0xfa2);
        std::bitset<16> baz (std::string("0101111001"));

        std::cout << "foo: " << foo << '\n';
        std::cout << "bar: " << bar << '\n';
        std::cout << "baz: " << baz << '\n';
    }

    // bitset的运算
    {
        std::bitset<4> foo (std::string("1001"));
        std::bitset<4> bar (std::string("0011"));

        std::cout << (foo  ^ = bar) << '\n';     // 1010 (XOR,assign)
        std::cout << (foo  & = bar) << '\n';     // 0010 (AND,assign)
        std::cout << (foo |  = bar) << '\n';     // 0011 (OR,assign)

        std::cout << (foo << = 2) << '\n';      // 1100 (SHL,assign)
        std::cout << (foo >> = 1) << '\n';      // 0110 (SHR,assign)

        std::cout << (~bar) << '\n';           // 1100 (NOT)
        std::cout << (bar << 1) << '\n';       // 0110 (SHL)
        std::cout << (bar >> 1) << '\n';       // 0001 (SHR)

        std::cout << (foo    == bar) << '\n';     // false (0110==0011)
        std::cout << (foo !  = bar) << '\n';     // true  (0110!=0011)

        std::cout << (foo & bar) << '\n';      // 0010
        std::cout << (foo | bar) << '\n';      // 0111
        std::cout << (foo ^ bar) << '\n';      // 0101
    }

    // bitset 相关函数
    {
#if 0
        foo.size() 返回大小（位数）
        foo.count() 返回1的个数
        foo.any() 返回是否有1
        foo.none() 返回是否没有1
        foo.set() 全都变成1
        foo.set(p) 将第p + 1位变成1
        foo.set(p, x) 将第p + 1位变成x
        foo.reset() 全都变成0
        foo.reset(p) 将第p + 1位变成0
        foo.flip() 全都取反
        foo.flip(p) 将第p + 1位取反
        foo.to_ulong() 返回它转换为unsigned long的结果，如果超出范围则报错
        foo.to_ullong() 返回它转换为unsigned long long的结果，如果超出范围则报错
        foo.to_string() 返回它转换为string的结果
#endif
    }

    cout << "Hello world!\n";

    return 0;
}