/*
输入一棵二叉树，求该树的深度。
定义：从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，
最长路径的长度为树的深度。
 */

#include <iostream>
#include <cmath>

using namespace std;


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
        val(x), left(NULL), right(NULL) {
    }
};

int TreeDepth(TreeNode *pRoot) {
    if(!pRoot)
        return 0;
    return max(1 + TreeDepth(pRoot->left), 1 + TreeDepth(pRoot->right));
}


int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}