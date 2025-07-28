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

// 二叉树 - 2.5 有递有归
class Solution {
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        // 自行解答，这个应该比较接近题解，很简洁
        auto dfs = [&] (this auto&& dfs, TreeNode* node, int val) -> TreeNode* {
            if (!node) return nullptr;
            if (!node->left && !node->right) 
                if (node->val + val < limit) return nullptr;
                else return node;
            
            node->left = dfs(node->left, val + node->val);
            node->right = dfs(node->right, val + node->val);
            // if (!node->left && !node->right) return nullptr;
            // else return node;
            return node->left || node->right ? node:nullptr;
        };

        return dfs(root, 0);
    }
};