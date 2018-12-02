/*
在一个字符串(0<=字符串长度<=10000，全部由字母组成)
中找到第一个只出现一次的字符,并返回它的位置,
如果没有则返回 -1（需要区分大小写）.
 */

#include <iostream>
#include <string>

using namespace std;

int FirstNotRepeatingChar(string str) {
    int len = str.size();
    if(len <= 0)
        return -1;

    int cnt[100] = {0}; //
    int i, res = -1;
    for(i = 0; i < len; i++) {
        cnt[str[i] - 'A']++;
    }

    for(i = 0; i < len; i++) {
        if(cnt[str[i] - 'A'] == 1) {
            res = i;
            break;
        }
    }
    return res;
}

int main(int argc, char const *argv[]) {
    //Test

    return 0;
}