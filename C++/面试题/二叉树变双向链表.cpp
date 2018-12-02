/*
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
 */

/*
解题思路：
先中序遍历，将所有的节点保存到一个列表中。
对这个list进行遍历，
每个节点的right设为下一个节点，
下一个节点的left设为上一个节点。
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

void convert2List(TreeNode *pRoot, TreeNode *&pointer) {
    if (pRoot == NULL) {
        return;
    }
    {
        if (pRoot->left != NULL) {
            convert2List(pRoot->left, pointer);
        }

        pRoot->left = pointer;
        if (pointer != NULL) {
            pointer->right = pRoot;
        }

        pointer = pRoot;
        if (pRoot->right != NULL) {
            convert2List(pRoot->right, pointer);
        }
    }
}

TreeNode *Convert(TreeNode *pRootOfTree) {
    if (pRootOfTree == NULL)
        return NULL;

    TreeNode *pointer = NULL;
    convert2List(pRootOfTree, pointer);

    while (pointer->left != NULL)
        pointer = pointer->left;

    return pointer;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}