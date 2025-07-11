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

// 二叉树 - 2.1 遍历二叉树 
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        // 自行解答
        vector<int> ans;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            if (node == nullptr) return;
            ans.push_back(node->val); dfs(node->left); dfs(node->right);
        };

        dfs(root);
        return ans;        
    }
};