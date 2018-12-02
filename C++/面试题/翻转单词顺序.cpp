/*
例如，“student. a am I”，正确的句子应该是“I am a student.”
 */

#include <iostream>
#include <string>

using namespace std;

void ReverseWord (string &str, int l, int r);

string ReverseSentence1(string str) {
    int size = str.size();
    if(size == 0)
        return "";

    int mark = 0;
    str += ' ';  //不严谨，严格来说是先去掉最后的空白，再添加一个空白
    for(int i = 0; i < size + 1; ++i) {
        if(str[i] == ' ') {
            ReverseWord(str, mark, i - 1);
            mark = i + 1;
        }
    }
    str = str.substr(0, size);
    ReverseWord(str, 0, size - 1);
    return str;
}

void ReverseWord (string &str, int l, int r) {
    while(l < r) {
        swap(str[l], str[r]); // 浪费空间
        ++l;
        --r;
    }
}

string ReverseSentence2(string str) {
    string res = "", tmp = "";
    for(unsigned int i = 0; i < str.size(); ++i) {
        if(str[i] == ' ')
            res = " " + tmp + res, tmp = "";
        else
            tmp += str[i];
    }
    if(tmp.size())
        res = tmp + res;
    return res;
}

int main(int argc, char const *argv[]) {
    /* code */
    string s("123 456");
    cout << ReverseSentence2(s);
    return 0;
}