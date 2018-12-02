/*
从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。
 */

#include <iostream>
#include <queue>
#include <vector>

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
    vector<vector<int> > vv;
    vector<int> ve;

    queue<TreeNode *> que;
    queue<int> dque;

    int depth = 0;
    que.push(pRoot);
    dque.push(depth);
    TreeNode *node;
    while(!que.empty()) {
        node = que.front();
        if(depth != dque.front()) {
            vv.push_back(ve);
            ve.clear();
            depth = dque.front();
        }
        que.pop();
        dque.pop();
        if(node) {
            que.push(node->left);
            que.push(node->right);
            dque.push(depth + 1);
            dque.push(depth + 1);
            ve.push_back(node->val);
        }
    }
    return vv;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}