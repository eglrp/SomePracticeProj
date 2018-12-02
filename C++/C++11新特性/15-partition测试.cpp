/*
 * Author: Neverland_LY
 * Date: 2018-11-16
 * ProjectName: partition
 * Version: v-1.0
 *
 * Description: https://blog.csdn.net/drecik__/article/details/79268840
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <forward_list>
#include <algorithm>
#include <iterator>

using namespace std;

template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last) {
    if(first == last) return;
    // std::next: 参数 --- 起始点，下一个距离当前iter的距离，返回 --- 指针
    // https://www.cnblogs.com/zhoutaotao/p/3833249.html
    auto pivot = *std::next(first, std::distance(first, last) / 2);
    ForwardIt middle1 = std::partition(first, last,
    [pivot](const auto & em) {
        return em < pivot;
    });
    quicksort(first, middle1);
    quicksort(std::next(middle1, 1), last);
}

int main() {
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "Original vector:\n    ";
    for (int elem : v) std::cout << elem << ' ';

    auto it = std::partition(v.begin(), v.end(), [](int i) {
        return i % 2 == 0;
    });

    std::cout << "\nPartitioned vector:\n    ";
    std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " * ";
    std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " "));
    // std::copy: 复制的起点，复制的终点，复制选项
    // https://blog.csdn.net/weixin_41353540/article/details/80634070
    // std::ostream_iterator: 复制到的流，分隔符
    // https://blog.csdn.net/lonelysky/article/details/51889495

    // std::forward_list: https://blog.csdn.net/elloop/article/details/50405783
    std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
    std::cout << "\nUnsorted list:\n    ";
    for(int n : fl) std::cout << n << ' ';
    std::cout << '\n';

    quicksort(std::begin(fl), std::end(fl));
    std::cout << "Sorted using quicksort:\n    ";
    for(int fi : fl) std::cout << fi << ' ';
    std::cout << '\n';

    return 0;
}
