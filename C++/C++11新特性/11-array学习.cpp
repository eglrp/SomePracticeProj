/*
 * Author: Neverland_LY
 * Date: 2018-11-16
 * ProjectName: Array
 * Version: v-1.0
 *
 * Description: https://www.cnblogs.com/DswCnblog/p/5671799.html
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <array>

using namespace std;

void Print(const array<int, 10> &arr) {
    for(auto iter = arr.begin(), end = arr.end(); iter != end; ++iter)
        cout << *iter << " "; // err: *iter += 1;, because read-only
    cout << "\n----------" << endl;
}

int main(int argc, char *argv[]) {

    // Todo...
    // 基本用法
    array<int, 10> arr{1, 2, 3, 4, 5, 6}; // 新的初始化方法
    Print(arr);
    arr[0] = 9; // 可以改变
    cout << arr.front() << endl;
    cout << arr.back() << endl;

    // data()
    const char *cstr = "Test string";
    array<char, 12> chararr;
    memcpy(chararr.data(), cstr, 12); // data() 取出元素的首地址
    cout << chararr.data() << endl;

    // fill()
    arr.fill(100); //全部替换为 100
    Print(arr);

    // swap()
    array<int, 10> arr1{1, 2, 3, 4, 5};
    array<int, 10> arr2 = {6, 7, 8, 9, 10};
    arr1.swap(arr2);
    Print(arr1);
    Print(arr2);

    // get<>
    cout << std::get<2>(arr1) << endl;
    std::get<2>(arr1) = std::get<1>(arr1) = std::get<0>(arr1);
    Print(arr1);

    // operator
    array<int, 5> a = {10, 20, 30, 40, 50};
    array<int, 5> b = {10, 20, 30, 40, 50};
    array<int, 5> c = {50, 40, 30, 20, 10};
    if (a == b) std::cout << "a and b are equal\n";
    if (b != c) std::cout << "b and c are not equal\n";
    if (b < c) std::cout << "b is less than c\n";
    if (c > b) std::cout << "c is greater than b\n";
    if (a <= b) std::cout << "a is less than or equal to b\n";
    if (a >= b) std::cout << "a is greater than or equal to b\n";

    cout << "Hello world!\n";



    return 0;
}