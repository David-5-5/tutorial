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
    string tree2str(TreeNode* root) {
        // 参考题解，四种情况
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> string {
            if (!node->left && !node->right) return to_string(node->val);
            else if (node->left && node->right) 
                return to_string(node->val) + "(" + dfs(node->left) + ")" +  "(" + dfs(node->right) + ")";
            else if (!node->left && node->right) 
                return to_string(node->val) + "()" +  "(" + dfs(node->right) + ")";
            else // (node->left && !node->right) 
                return to_string(node->val) +  "(" + dfs(node->left) + ")";
        };

        return dfs(root); 
    }
};