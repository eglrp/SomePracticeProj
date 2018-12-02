/*
给定一棵二叉搜索树，请找出其中的第k小的结点。
例如，（5，3，7，2，4，6，8）中，按结点数值大小顺序第三小结点的值为4
 */

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
        val(x), left(NULL), right(NULL) {
    }
};

TreeNode *KthNode(TreeNode *pRoot, unsigned int k) {
    int count = 0;
    if(pRoot) {
        TreeNode *ret = KthNode(pRoot->left, k);
        if(ret) 
            return ret;
        if(++count == k) 
            return pRoot;
        ret = KthNode(pRoot->right, k);
        if(ret) 
            return ret;
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}