#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

/*
template< class InputIt, class OutputIt, class UnaryOperation >
OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first,
                    UnaryOperation unary_op );

std::transform 应用给定的函数到范围并存储结果于始于 d_first 的另一范围。


 */

int main() {
  std::string s("hello");
  std::transform(s.begin(), s.end(), s.begin(),
           [](unsigned char c) -> unsigned char { return std::toupper(c); });


  std::vector<std::size_t> ordinals; // 不知道有什么用意
  std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
           [](unsigned char c) -> std::size_t { return c; });

  std::cout << s << ':';
  for (auto ord : ordinals) {
    std::cout << ' ' << ord;
  }
}