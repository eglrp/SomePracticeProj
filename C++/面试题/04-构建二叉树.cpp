/*
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
 */

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> in) {
    int inlen = in.size();
    if(inlen == 0)
        return NULL;

    vector<int> left_pre, right_pre, left_in, right_in;
    //创建根节点，根节点肯定是前序遍历的第一个数
    TreeNode *head = new TreeNode(pre[0]);
    //找到中序遍历根节点所在位置,存放于变量gen中
    int gen = 0;
    for(int i = 0; i < inlen; i++) {
        if (in[i] == pre[0]) {
            gen = i;
            break;
        }
    }
    //对于中序遍历，根节点左边的节点位于二叉树的左边，根节点右边的节点位于二叉树的右边
    //利用上述这点，对二叉树节点进行归并
    for(int i = 0; i < gen; i++) {
        left_in.push_back(in[i]);
        left_pre.push_back(pre[i + 1]); //前序第一个为根节点
    }

    for(int i = gen + 1; i < inlen; i++) {
        right_in.push_back(in[i]);
        right_pre.push_back(pre[i]);
    }

    //和shell排序的思想类似，取出前序和中序遍历根节点左边和右边的子树
    //递归，再对其进行上述所有步骤，即再区分子树的左、右子子数，直到叶节点
    head->left = reConstructBinaryTree(left_pre, left_in);
    head->right = reConstructBinaryTree(right_pre, right_in);

    return head;
}

vector<vector<int> > Print(TreeNode *pRoot) {
    vector<vector<int> > Value;
    if (pRoot == NULL)
        return Value;
    queue<TreeNode * > queNode;
    queNode.push(pRoot);
    vector<int> subValue;                               //辅助数组，保存当前层所有的结点值
    int nextLevels = 0;                                 //用来统计下一层的结点数
    int currentLevels = 1;                              //用来标记当前层剩余的没有打印的结点数
    while (!queNode.empty()) {
        TreeNode *pNode = queNode.front();
        queNode.pop();
        subValue.push_back(pNode->val);
        if (pNode->left != NULL) {
            queNode.push(pNode->left);
            ++nextLevels;
        }

        if (pNode->right != NULL) {
            queNode.push(pNode->right);
            ++nextLevels;
        }
        --currentLevels;
        if (currentLevels == 0) {                           //如果当前层结点已全部打印完毕
            Value.push_back(subValue);
            subValue.clear();                           //清空，开始存下一层结点
            currentLevels = nextLevels;                 //下一层要打印的结点数
            nextLevels = 0;                             //置0，开始统计下一层结点数
        }
    }
    return Value;
}

void plr(TreeNode *pRoot) {
    if(pRoot != NULL) {
        cout << pRoot->val << endl;
        if(pRoot->left != NULL)
            cout << "left  " << pRoot->left->val << endl;
        if(pRoot->right != NULL)
            cout << "right  " << pRoot->right->val << endl;
    }
}

int main(int argc, char const *argv[]) {
    // Test
    // 创建 vec_pre vec_in
    int arr_pre[8] = {1, 2, 4, 7, 3, 5, 6, 8};
    vector<int> vec_pre(arr_pre, arr_pre + 8);
    int arr_in[8] = {4, 7, 2, 1, 5, 3, 8, 6};
    vector<int> vec_in(arr_in, arr_in + 8);

    struct TreeNode *head = reConstructBinaryTree(vec_pre, vec_in);

    vector<vector<int> > list(Print(head));
    for(int i = 0; i < list.size(); i++) {
        for(int j = 0; j < list[i].size(); j++) {
            cout << list[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

