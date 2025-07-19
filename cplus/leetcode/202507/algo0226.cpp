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
    TreeNode* invertTree(TreeNode* root) {
        // 自行解答
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            if (node == nullptr) return;
            auto left = node->left;     // 需要临时变量
            node->left = node->right, node->right = left;
            dfs(node->right); dfs(node->left); 
        };

        dfs(root);
        return root;     
    }

    TreeNode* invertTree(TreeNode* root) {
        // 参考题解
        if (root == nullptr) return root;
        auto left = invertTree(root->left);
        auto right = invertTree(root->right);
        root->left = right;
        root->right = left;

        return root;     
    }    
};