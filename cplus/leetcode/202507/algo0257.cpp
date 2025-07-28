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

// 二叉树 - 2.7 回溯
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        // 自行解答
        vector<string> ans;
        auto dfs = [&](this auto&& dfs, TreeNode* node, string pre) -> void {
            if (!node->left && !node->right) ans.push_back(pre);
            
            if (node->left) dfs(node->left, pre + "->" + to_string(node->left->val));
            if (node->right) dfs(node->right, pre + "->" + to_string(node->right->val));
        };

        dfs(root, to_string(root->val));
        return ans;
    }
};