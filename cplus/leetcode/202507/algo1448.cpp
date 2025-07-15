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
    int goodNodes(TreeNode* root) {
        
        auto dfs = [](this auto&& dfs, TreeNode* node, int premax) -> int {
            if (!node) return 0;
            
            int res = (node->val >= premax);
            res += dfs(node->left, max(premax, node->val));
            res += dfs(node->right, max(premax, node->val));
            return res;
        };
        return dfs(root, root->val);
    }
};