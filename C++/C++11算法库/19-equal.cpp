/* 下面的代码使用 equal() 来测试字符串是否是回文 */

#include <iostream>
#include <algorithm>
#include <string>

void test(const std::string &s) {
    if(std::equal(s.begin(), s.begin() + s.size() / 2, s.rbegin())) {
        std::cout << "\"" << s << "\" is a palindrome\n";
    } else {
        std::cout << "\"" << s << "\" is not a palindrome\n";
    }
}
int main() {
    test("radar");
    test("hello");
}