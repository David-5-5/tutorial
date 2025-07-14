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
    int minDepth(TreeNode* root) {
        auto dfs = [](this auto&& dfs, TreeNode* node) -> int {
            if (!node) return 0;
            if (!node->left && !node->right) return 1;
            
            int depth = INT_MAX;
            if (node->left) depth = min(depth, dfs(node->left));
            if (node->right) depth = min(depth, dfs(node->right)) ;
            return depth + 1;
        };
        return dfs(root);        
    }

    int minDepth2(TreeNode* root) {
        if (root == nullptr) return 0;
        int ans = INT_MAX;

        auto dfs = [&](this auto&& dfs, TreeNode* node, int d) -> void {
            if (!node->left && !node->right) ans = min(ans, d);
            
            if (node->left) dfs(node->left, d+1);
            if (node->right) dfs(node->right, d+1);
        };
        dfs(root, 1);
        return ans;
    }
};