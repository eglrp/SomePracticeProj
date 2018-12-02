/*
输入两棵二叉树A，B，判断B是不是A的子结构。
（ps：我们约定空树不是任意一个树的子结构）
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

    bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2) {
        if(!pRoot1)
            return false; // A 树不能为空

        if(!pRoot2)
            return false; // 空树不是任何树的子树

        // 对于每一个结点，必须判断当前结点以及当前结点的左右子树
        return ( dfs(pRoot1, pRoot2)) ||
               HasSubtree(pRoot1->left, pRoot2) ||
               HasSubtree(pRoot1->right, pRoot2);
    }

private:
    bool dfs(TreeNode *r1, TreeNode *r2) {
        if(!r2)
            return true;  // 如果 r2 是空的话，不管左子树是不是空，那么 r2 一定是 r1 的子树 (r1 >= r2)

        if(!r1)
            return false;  // 这种情况属于 r2 为空，r1 为空，那么肯定不是子树

        if(r1->val != r2->val) // 结点都不为空的话，就比较值是否相等
            return false;

        return dfs(r1->left, r2->left) && dfs(r1->right, r2->right); // 迭代
    }
};

int main(int argc, char const *argv[]) {
    //测试用例略
    //
    return 0;
}