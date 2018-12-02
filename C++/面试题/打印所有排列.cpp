/*
输入一个字符串,按字典序打印出该字符串中字符的所有排列。
例如输入字符串abc,则打印出由字符a,b,c所能排列出来的
所有字符串abc,acb,bac,bca,cab和cba。
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    vector<string> permutation;
    set<string> permutationSet;

    vector<string> Permutation(string str) {
        if (str.size() != 0) {
            int nSize = str.size();
            Permutation(str, nSize, 0);
        }
        for (set<string>::iterator iter = permutationSet.begin();
                iter != permutationSet.end(); ++iter) {
            permutation.push_back(*iter);
        }
        return permutation;
    }

    void Permutation(string str, int nSize, int n) {
        if (n == str.size()) {  //把自己添加进去
            permutationSet.insert(str);
        } else {
            Permutation(str, nSize, n + 1);
            for (int i = n + 1; i < str.size(); ++i) {
                if (str[n] != str[i]) {
                    char tmp = str[n];
                    str[n] = str[i];
                    str[i] = tmp;

                    Permutation(str, nSize, n + 1);

                    tmp = str[n];
                    str[n] = str[i];
                    str[i] = tmp;
                }
            }
        }
    }
};

int main(int argc, char const *argv[]) {
    /* code */
    for(int i = 1; i < 1; ++i) {
        string s("123");
        cout << s.size();
    }

    return 0;
}