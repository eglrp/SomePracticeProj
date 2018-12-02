/*
 * Author: Neverland_LY
 * Date: 2018-11-19
 * ProjectName: for_each
 * Version: v-1.0
 *
 * Description: https://zh.cppreference.com/w/cpp/algorithm/for_each
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
    template< class InputIt, class UnaryFunction >
    UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );

    按顺序应用给定的函数对象 f 到解引用范围 [first, last) 中每个迭代器的结果。
     */

    std::vector<int> nums{3, 4, 2, 8, 15, 267}; // initilize_list

    auto print = [](const int &n) {
        std::cout << " " << n;
    };

    std::cout << "before:";
    std::for_each(nums.begin(), nums.end(), print);
    std::cout << '\n';

    std::for_each(nums.begin(), nums.end(), [](int &n) {
        n++;
    });


    struct Sum {
        Sum(): sum{0} { }
        void operator()(int n) {
            sum += n;
        }
        int sum;
    };

    // 对每个数调用 Sum::operator()
    Sum s = std::for_each(nums.begin(), nums.end(), Sum());

    std::cout << "after: ";
    std::for_each(nums.begin(), nums.end(), print);
    std::cout << '\n';
    std::cout << "sum: " << s.sum << '\n';

    cout << "Hello world!\n";

    return 0;
}