#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>

/* 复制来自范围 [first, last) 的元素到始于 d_first 的另一范围，省略满足特定判别标准的元素。源与目标范围不能重叠。 */
int main() {
    std::string str = "Text with some   spaces";
    std::cout << "before: " << str << "\n";

    std::cout << "after:  ";
    std::remove_copy(str.begin(), str.end(),
                     std::ostream_iterator<char>(std::cout), ' ');
    std::cout << '\n';
}