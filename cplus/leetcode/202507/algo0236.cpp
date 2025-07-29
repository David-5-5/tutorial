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

// 二叉树 - 2.8 最近公共祖先
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 复习 LCA 经典
        auto lca = [&] (this auto&& dfs, TreeNode* node) -> TreeNode* {
            if (!node || node == p || node == q) return node;
            auto lson = dfs(node->left);
            auto rson = dfs(node->right);
            if (lson && rson) return node;
            return lson?lson:rson;
        };

        return lca(root);        
    }
};