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
    int findTilt(TreeNode* root) {
        int sum = 0;
        auto dfs = [&] (this auto&& dfs, TreeNode* node) -> int {
            if (node == nullptr) return 0;
            auto left = dfs(node->left);
            auto right = dfs(node->right);
            sum += abs(left-right); return node->val + left + right;
        };

        dfs(root);
        return sum;
    }
};