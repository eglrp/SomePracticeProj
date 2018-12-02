/*
 * Author: Neverland_LY
 * Date: 2018-11-19
 * ProjectName: mismatch
 * Version: v-1.0
 *
 * Description: https://zh.cppreference.com/w/cpp/algorithm/mismatch
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

std::string mirror_ends(const std::string &in) {
    return std::string(in.begin(),
                       std::mismatch(in.begin(), in.end(), in.rbegin()).first);
}


int main(int argc, char *argv[]) {

    /*

    template< class InputIt1, class InputIt2 >
    std::pair<InputIt1,InputIt2>
    mismatch( InputIt1 first1, InputIt1 last1,
              InputIt2 first2 );

              返回来自二个范围：一个以 [first1, last1) 定义而另一个以 [first2,last2) 定义，的首个不匹配对。
              若不提供 last2 （重载 (1-4) ），则它指代 first2 + (last1 - first1) 。

    1,5) 用 operator== 比较元素。
    3,7) 用给定的二元谓词 p 比较元素。


     */

    std::cout << mirror_ends("abXYZba") << '\n'
              << mirror_ends("abca") << '\n'
              << mirror_ends("aba") << '\n';




    cout << "Hello world!\n";

    return 0;
}