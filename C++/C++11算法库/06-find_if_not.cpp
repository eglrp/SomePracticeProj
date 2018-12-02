/*
 * Author: Neverland_LY
 * Date: 2018-11-19
 * ProjectName: find_if_not
 * Version: v-1.0
 *
 * Description: https://zh.cppreference.com/w/cpp/algorithm/find
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

// C++11 / 14
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <condition_variable>

using namespace std;

class CLASSNAME {
public:
    CLASSNAME() {}
    ~CLASSNAME() {}
private:

};

int main(int argc, char *argv[]) {

    /*

    template< class InputIt, class T >
    InputIt find( InputIt first, InputIt last, const T& value );


    返回范围 [first, last) 中满足特定判别标准的首个元素：

    1) find 搜索等于 value 的元素。
    3) find_if 搜索谓词 p 对其返回 true 的元素。
    5) find_if_not 搜索谓词 q 对其返回 false 的元素。

     */

    int n1 = 3;
    int n2 = 5;

    std::vector<int> v{0, 1, 2, 3, 4};

    auto result1 = std::find(std::begin(v), std::end(v), n1);
    auto result2 = std::find(std::begin(v), std::end(v), n2);

    if (result1 != std::end(v)) {
        std::cout << "v contains: " << n1 << '\n';
    } else {
        std::cout << "v does not contain: " << n1 << '\n';
    }

    if (result2 != std::end(v)) {
        std::cout << "v contains: " << n2 << '\n';
    } else {
        std::cout << "v does not contain: " << n2 << '\n';
    }


    cout << "Hello world!\n";

    return 0;
}