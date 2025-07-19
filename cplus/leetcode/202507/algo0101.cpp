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

// 二叉树 - 2.3 自底向上 DFS
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // 自行节点，左右交换的技巧
        // 要是没有训练过，虽然是简单题，还真不容易做
        if (root == nullptr) return true;

        auto dfs = [&] (this auto&& dfs, TreeNode* u, TreeNode* v) -> bool {
            if (u == nullptr && v == nullptr) return true;
            if (u == nullptr && v != nullptr) return false;
            if (u != nullptr && v == nullptr) return false;
            
            if (u->val != v->val) return false;

            return dfs(u->left, v->right) && dfs(u->right, v->left);

        };

        return dfs(root->left, root->right);
    }
};