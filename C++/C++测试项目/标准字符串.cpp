#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    //char p[5] = "12345";
    char q[5] = "1234";

    //printf("%s\n", p);
    printf("%s\n", q);

    std::vector<int> v(10'000'007, 0.5);  // 不知道什么意思
    for(auto i : v) std::cout << i << ' ';

    return 0;
}