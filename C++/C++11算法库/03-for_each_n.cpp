/*
 * Author: Neverland_LY
 * Date: 2018-11-19
 * ProjectName: for_each_n
 * Version: v-1.0
 *
 * Description: Description
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


int main(int argc, char *argv[]) {

    /*
    template< class InputIt, class Size, class UnaryFunction >
    InputIt for_each_n( InputIt first, Size n, UnaryFunction f );

    按顺序应用给定的函数对象 f 到解引用范围 [first, first + n) 中每个迭代器的结果。
     */


    std::vector<int> ns{1, 2, 3, 4, 5};
    for (auto n : ns) std::cout << n << ", ";
    std::cout << '\n';
    std::for_each_n(ns.begin(), 3, [](auto & n) {
        n *= 2;
    });
    for (auto n : ns) std::cout << n << ", ";
    std::cout << '\n';


    cout << "Hello world!\n";

    return 0;
}

/*
output:

1, 2, 3, 4, 5,
2, 4, 6, 4, 5,

 */