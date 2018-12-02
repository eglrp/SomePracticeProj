#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>

int main() {
    std::vector<int> v{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::replace_copy_if(v.begin(), v.end(),
                         std::ostream_iterator<int>(std::cout, " "),
    [](int n) {
        return n > 5;
    }, 99);
    std::cout << '\n';
}