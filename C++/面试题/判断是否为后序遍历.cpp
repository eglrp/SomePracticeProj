/*
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
如果是则输出Yes,否则输出No。
假设输入的数组的任意两个数字都互不相同。
 */

#include <iostream>
#include <vector>

using namespace std;

bool bst(vector<int> sequence, int begin, int end) {
    if(sequence.empty() || begin > end)
        return false;

    int root = sequence[end];
    int i = begin;
    for(; i < end; ++i)
        if(sequence[i] > root) //i坐标为右子树第一个节点
            break;
    for(int j = i; j < end; ++j) // j在i的基础上继续加
        if(sequence[j] < root)
            return false;

    bool left = true;
    if(i > begin)
        left = bst(sequence, begin, i - 1);
    bool right = true;
    if(i < end - 1)
        right = bst(sequence, i, end - 1);
    return left && right;
}

bool VerifySquenceOfBST(vector<int> sequence) {
    return bst(sequence, 0, sequence.size() - 1);
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}