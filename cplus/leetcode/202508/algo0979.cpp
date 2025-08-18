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

// 二叉树 - 2.16 其他
class Solution {
public:
    int distributeCoins(TreeNode* root) {
        // 自行解答
        int ans = 0;

        auto dfs = [&](this auto&& dfs, TreeNode* node) -> int {
            if (!node) return 0;
            int left_diff = dfs(node->left);
            int right_diff = dfs(node->right);
            ans += abs(left_diff + right_diff + node->val - 1);
            return left_diff + right_diff + node->val - 1;
        };

        dfs(root);
        return ans;              
    }
};