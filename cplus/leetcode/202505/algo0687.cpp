#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.1 树的直径

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
    int longestUnivaluePath(TreeNode* root) {
        // 自行解答
        int ans = 0;

        auto dfs = [&](this auto&& dfs, TreeNode* node) -> int{
            if (node == nullptr) return 0;
            int dia = 0, res = 0;

            int left = dfs(node->left), right = dfs(node->right);
            if (node->left && node->val == node->left->val) dia += 1 + left, res = max(res, 1+left);
            if (node->right && node->val == node->right->val) dia += 1 + right, res = max(res, 1+ right);

            ans = max(ans, dia);
            return res;
        };
        
        dfs(root);
        return ans;
    }
};