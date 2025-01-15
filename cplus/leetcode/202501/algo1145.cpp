#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 思维题 - 从特殊到一般
/**
 * Definition for a binary tree node.
 */

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        // 自行阶段
        // 练习 c++ 指针 树 遍历
        function<TreeNode*(TreeNode*)> find = [&](TreeNode* node) -> TreeNode* {
            if (node == nullptr) return NULL;
            if (node->val == x) return node;
            TreeNode* chd = find(node->left);  // 左节点
            if (chd != NULL) return chd;
            return find(node->right);         // 右节点
        };

        function<int(TreeNode*)> count = [&] (TreeNode* node) -> int {
            if (node == NULL) return 0;
            return 1 + count(node->left) + count(node->right); 
        };

        TreeNode* xNode = find(root);        // 查找值 为 x 的节点
        int cnt = count(xNode->left);           // 选择 x 左节点
        cnt = max(cnt, count(xNode->right));    // 选择 x 右节点
        if (xNode!=root) cnt = max(cnt, n - count(xNode));    // 选择 x 的父节点

        return cnt > n - cnt;
    }
};