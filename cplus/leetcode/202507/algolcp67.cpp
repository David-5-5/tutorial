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
    TreeNode* expandBinaryTree(TreeNode* root) {
        // 自行解答
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            if (node->left) {
                TreeNode* tr = new TreeNode(-1, node->left, nullptr);
                node->left = tr;
                dfs(tr->left);
            }
            if (node->right) {
                TreeNode* tr = new TreeNode(-1, nullptr, node->right);
                node->right = tr;
                dfs(tr->right);
            }
        };

        dfs(root);
        return root;
    }
};