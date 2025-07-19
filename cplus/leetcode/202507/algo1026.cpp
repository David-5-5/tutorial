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
    int maxAncestorDiff(TreeNode* root) {
        // 自行解答
        int ans = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> pair<int, int> {
            if (!node->left && !node->right) {
                return {node->val, node->val};
            }

            int mn = INT_MAX, mx = 0;
            if (node->left) {
                auto left = dfs(node->left);
                mn = min(mn, left.first); mx = max(mx, left.second);
            }
            if (node->right) {
                auto right = dfs(node->right);
                mn = min(mn, right.first); mx = max(mx, right.second);
            }
            ans = max(ans, abs(node->val-mn)); ans = max(ans, abs(node->val-mx));
            return {min(mn, node->val), max(mx, node->val)};
        };

        dfs(root);
        return ans;
    }
};