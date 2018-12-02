/*
输入一棵二叉树，判断该二叉树是否是平衡二叉树。
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

class Solution {
public:
    bool IsBalanced_Solution(TreeNode *pRoot) {
        if(pRoot == NULL)
            return true;
        //自上而下判断，以每一层为初始层向下判断是否平衡
        int leftDepth = getDepth(pRoot -> left);
        int rightDepth = getDepth(pRoot -> right);
        if(leftDepth > rightDepth + 1 || leftDepth + 1 < rightDepth)
            return false;
        else
            return IsBalanced_Solution(pRoot -> left) &&
                   IsBalanced_Solution(pRoot -> right);
    }

    int getDepth(TreeNode *pRoot) {
        if(pRoot == NULL)
            return 0;
        int leftDepth = getDepth(pRoot -> left);
        int rightDepth = getDepth(pRoot -> right);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
};

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}