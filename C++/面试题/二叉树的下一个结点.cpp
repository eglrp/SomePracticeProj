/*
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
 */

///注意对中序遍历的理解！！！

#include <iostream>

using namespace std;

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {

    }
};

TreeLinkNode *GetNext(TreeLinkNode *pNode) {
    if(pNode == NULL)
        return NULL;

    TreeLinkNode *next = NULL;
    //先右子节点的左子节点遍历
    if(pNode->right != NULL) {
        TreeLinkNode *rightNode  = pNode->right;
        while(rightNode->left != NULL) {
            rightNode = rightNode->left;
        }
        next = rightNode;
    }
    //向父结点遍历
    else if(pNode->next != NULL) {
        TreeLinkNode *parentNode = pNode->next;
        TreeLinkNode *currentNode = pNode;
        while(parentNode != NULL  && currentNode == parentNode->right) {
            currentNode = parentNode;
            parentNode = parentNode->next;
        }
        next = parentNode;
    }
    return next;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}