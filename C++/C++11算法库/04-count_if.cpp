/*
 * Author: Neverland_LY
 * Date: 2018-11-19
 * ProjectName: count_if
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
    template< class InputIt, class T >
    typename iterator_traits<InputIt>::difference_type
    count( InputIt first, InputIt last, const T &value );

    返回范围 [first, last) 中满足特定判别标准的元素数。

    1) 计数等于 value 的元素。
    3) 计数谓词 p 对其返回 true 的元素。

     */

    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

    // 确定 std::vector 中有多少个整数匹配目标值。
    int target1 = 3;
    int target2 = 5;
    int num_items1 = std::count(v.begin(), v.end(), target1);
    int num_items2 = std::count(v.begin(), v.end(), target2);
    std::cout << "number: " << target1 << " count: " << num_items1 << '\n';
    std::cout << "number: " << target2 << " count: " << num_items2 << '\n';

    // 用 lambda 表达式计量能被 3 整除的元素数。
    int num_items3 = std::count_if(v.begin(), v.end(), [](int i) {
        return i % 3 == 0;
    });
    std::cout << "number divisible by three: " << num_items3 << '\n';


    cout << "Hello world!\n";

    return 0;
}