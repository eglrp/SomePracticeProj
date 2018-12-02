/*
请实现一个函数按照之字形打印二叉树，
即第一行按照从左到右的顺序打印，
第二层按照从右至左的顺序打印，
第三行按照从左到右的顺序打印，
其他行以此类推。
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
        val(x), left(NULL), right(NULL) {
    }
};

vector<vector<int> > Print(TreeNode *pRoot) {
    vector<vector<int> > res;
    if(pRoot == nullptr)
        return res;

    stack<TreeNode *> stackL;
    stack<TreeNode *> stackR;

    TreeNode *popNode;
    vector<int> tmp;

    tmp.push_back(pRoot->val);
    res.push_back(tmp);
    tmp.clear();

    stackL.push(pRoot);
    while(!stackL.empty() || !stackR.empty()) {
        while(!stackL.empty()) {
            popNode = stackL.top();
            stackL.pop();
            if(popNode->right) {
                stackR.push(popNode->right);
                tmp.push_back(popNode->right->val);
            }
            if(popNode->left) {
                stackR.push(popNode->left);
                tmp.push_back(popNode->left->val);
            }
        }
        if(!tmp.empty()) {
            res.push_back(tmp);
            tmp.clear();
        }
        while(!stackR.empty()) {
            popNode = stackR.top();
            stackR.pop();
            if(popNode->left) {
                stackL.push(popNode->left);
                tmp.push_back(popNode->left->val);
            }
            if(popNode->right) {
                stackL.push(popNode->right);
                tmp.push_back(popNode->right->val);
            }
        }
        if(!tmp.empty()) {
            res.push_back(tmp);
            tmp.clear();
        }
    }
    return res;
}

int main(int argc, char const *argv[]) {
    /* code */

    return 0;
}