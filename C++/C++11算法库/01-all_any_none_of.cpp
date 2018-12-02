/*
 * Author: Neverland_LY
 * Date: 2018-11-19
 * ProjectName: all_of any_of none_of
 * Version: v-1.0
 *
 * Description: https://zh.cppreference.com/w/cpp/algorithm/all_any_none_of
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

#include <random>
#include <list>

using namespace std;


int main(int argc, char *argv[]) {

    {
        // partial_sum
        std::vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // 或 std::vector<int>v(10, 2);
        std::cout << "The first 10 even numbers are: ";
        // template< class InputIt, class OutputIt > OutputIt partial_sum( InputIt first, InputIt last, OutputIt d_first );
        // 计算范围 [first, last) 的子范围中元素的部分和，并写入到始于 d_first 的范围
        std::partial_sum(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';

        std::partial_sum(v.begin(), v.end(), v.begin(), std::multiplies<int>()); // C++14，进行乘法的函数对象（全特化）
        std::cout << "The first 10 powers of 2 are: ";
        for (auto n : v) {
            std::cout << n << " ";
        }
        std::cout << '\n';
    }

    {
        /*
        template< class ForwardIterator, class T >
        void iota( ForwardIterator first, ForwardIterator last, T value );
        (C++11 起)

        以始于 value 并重复地求值 ++value 的顺序递增值填充范围 [first, last) 。
         */

        std::list<int> l(10);
        std::iota(l.begin(), l.end(), -4);

        std::vector<std::list<int>::iterator> v(l.size());
        std::iota(v.begin(), v.end(), l.begin());

        std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});

        std::cout << "Contents of the list: ";
        for(auto n : l) std::cout << n << ' ';
        std::cout << '\n';

        std::cout << "Contents of the list, shuffled: ";
        for(auto i : v) std::cout << *i << ' ';
        std::cout << '\n';
    }

    {
        /*
        template< class RandomIt >
        void random_shuffle( RandomIt first, RandomIt last );

        重排序给定范围 [first, last) 中的元素，使得这些元素的每个排列拥有相等的出现概率。

         */

        std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(v.begin(), v.end(), g);

        std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";
    }

    {
        // std::copy
        // template< class InputIt, class OutputIt > OutputIt copy( InputIt first, InputIt last, OutputIt d_first );
        // 复制范围 [first, last) 中的所有元素，从首元素开始逐次到末元素。
        // 若 d_first 在范围 [first, last) 中则行为未定义。此情况下可用 std::copy_backward 代替。
        //
        // copy_if
        // 仅复制谓词 pred 对其返回 true 的元素。保持被复制元素的相对顺序。若源与目标范围重叠则行为未定义。

        std::vector<int> from_vector(10);
        std::iota(from_vector.begin(), from_vector.end(), 0);

        std::vector<int> to_vector;
        std::copy(from_vector.begin(), from_vector.end(),
                  std::back_inserter(to_vector));
        // 或可选地，
        //  std::vector<int> to_vector(from_vector.size());
        //  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
        // 任一方式都等价于
        //  std::vector<int> to_vector = from_vector;

        std::cout << "to_vector contains: ";

        std::copy(to_vector.begin(), to_vector.end(),
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';

    }


    std::vector<int> v(10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";

    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    if (std::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0;})) {
        std::cout << "All numbers are even\n";
    }

    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), std::placeholders::_1, 2))) { // X / 2
        std::cout << "None of them are odd\n";
    }

    struct DivisibleBy {
        const int d;
        DivisibleBy(int n) : d(n) {}
        bool operator()(int n) const {
            return n % d == 0;
        }
    };

    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) { // x % 7
        std::cout << "At least one number is divisible by 7\n";
    }

    cout << "Hello world!\n";

    return 0;
}