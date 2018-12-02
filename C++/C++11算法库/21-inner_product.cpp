#include <numeric>
#include <iostream>
#include <vector>
#include <functional>

/*

template<class InputIt1, class InputIt2, class T,
         class BinaryOperation1, class BinaryOperation2>
T inner_product( InputIt1 first1, InputIt1 last1,
                 InputIt2 first2, T init,
                 BinaryOperation1 op1,
                 BinaryOperation2 op2 );


以表达式 acc = op1(acc, op2(*first1, *first2)) 修改它，
再以表达式 acc = op1(acc, op2(*(first1+1), *(first2+1))) 修改它，以此类推

 */

int main() {
    std::vector<int> a{0, 1, 2, 3, 4};
    std::vector<int> b{5, 4, 2, 3, 1};

    int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 1);
    std::cout << "Inner product of a and b: " << r1 << '\n';

    int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<>(), std::equal_to<>()); // std::equal_to<> 相等的情况返回的是 true，相当于是 1
    std::cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';
}