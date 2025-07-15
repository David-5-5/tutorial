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

// 二叉树 - 2.2 自顶向下 DFS
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {

        auto dfs = [](this auto&& dfs, TreeNode* node, int rem) -> bool {
            if (node == nullptr) return false;
            if (!node->left && !node->right) return rem == node->val;
            
            return dfs(node->left, rem- node->val) ||
                    dfs(node->right, rem- node->val);
        };

        return dfs(root, targetSum);
    }   
};