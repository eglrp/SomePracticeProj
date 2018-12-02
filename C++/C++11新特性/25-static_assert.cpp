/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: no
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

static_assert(sizeof(void *) == 8, "64-bit code generation is not supported.");
//该 static_assert 用来确保编译仅在 32 位的平台上进行，不支持 64 位的平台，该语句可以放
//在文件的开头处，这样可以尽早检查，以节省失败情况下的编译时间。

template<typename T, typename U>
int my_bit_copy(T &a, U &b) {
    static_assert(sizeof(a) == sizeof(b), "parameters must have same width");
}

int main(int argc, char *argv[]) {
    int a;
    float b;
    my_bit_copy(a, b);
    char c;
    //my_bit_copy(a, c);  // 编译不过
    return 0;
}