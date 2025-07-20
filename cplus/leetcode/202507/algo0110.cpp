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
    bool isBalanced(TreeNode* root) {
        // 自行解答
        bool ans = true;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> int {
            if (node == nullptr) return 0;

            int left = dfs(node->left);
            int right = dfs(node->right);
            if (abs(left-right)>1) ans = false;
            return max(left, right) + 1;
        };
        dfs(root);
        return ans;   
    }
};