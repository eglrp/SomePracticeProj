/*
操作给定的二叉树，将其变换为源二叉树的镜像。

二叉树的镜像定义：
源二叉树
            8
           /  \
          6   10
         / \  / \
        5  7 9 11

镜像二叉树
            8
           /  \
          10   6
         / \  / \
        11 9 7  5

*/

#include <iostream>

using namespace std;

struct TreeNode { // 简洁高效
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
        val(x), left(NULL), right(NULL) {
    }
};

void Mirror1(TreeNode *pRoot) {
    if (pRoot == NULL)
        return;

    TreeNode *pTmp;
    pTmp = pRoot->left;
    pRoot->left = pRoot->right;
    pRoot->right = pTmp;
    Mirror1(pRoot->left);
    Mirror1(pRoot->right);
}

void Mirror2(TreeNode *pRoot) {
    if (pRoot->left) {
        Mirror2(pRoot->left);

        TreeNode *pTmp;
        pTmp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = pTmp;
    }

    if (pRoot->right) {
        Mirror2(pRoot->right);

        TreeNode *pTmp;
        pTmp = pRoot->right;
        pRoot->right = pRoot->left;
        pRoot->left = pTmp;
    }
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
