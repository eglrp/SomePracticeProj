/*
从上往下打印出二叉树的每个节点，同层节点从左至右打印。
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
        val(x), left(NULL), right(NULL) {
    }
};

vector<int> PrintFromTopToBottom(TreeNode *root) {
    vector<int> que;
    if(root == NULL)
        return que;

    queue<TreeNode *>q;
    TreeNode *fr;
    q.push(root);

    while(!q.empty()) {
        fr = q.front();
        que.push_back(fr->val);
        if(fr->left != NULL)
            q.push(fr->left);
        if(fr->right != NULL)
            q.push(fr->right);
        q.pop();
    }

    return que;
}

int main(int argc, char const *argv[]) {
    //Test
    //自行测试，很简单
    return 0;
}