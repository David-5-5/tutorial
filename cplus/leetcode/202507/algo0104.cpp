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
    int maxDepth(TreeNode* root) {
        
        auto dfs = [](this auto&& dfs, TreeNode* node) -> int {
            if (!node) return 0;
            return max(dfs(node->left), dfs(node->right)) + 1;
        };
        return dfs(root);
    }
};