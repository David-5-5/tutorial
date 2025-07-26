#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 二叉树 - 2.4 自底向上 DFS：删点
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        // 自行解答
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> int {
            if (!node->left && !node->right) return node->val;
            int res = node->val;
            if (node->left) {
                auto left = dfs(node->left);
                if (left == 0) node->left = nullptr;
                else res += left;
            }
            if (node->right) {
                auto right = dfs(node->right);
                if (right == 0) node->right = nullptr;
                else res += right;
            }
            return res;
        };

        auto cnt = dfs(root);
        return cnt?root:nullptr;
    }

    TreeNode* pruneTree(TreeNode* root) {
        // 自行解答 - 简化
        if (!root) return nullptr;
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);

        if (!root->left && !root->right && !root->val) return nullptr;
        else return root;
    }
};