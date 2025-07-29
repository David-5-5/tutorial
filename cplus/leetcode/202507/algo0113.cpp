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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (!root) return {};   // root 可以为空
        vector<vector<int>> ans;
        
        auto dfs = [&](this auto&& dfs, TreeNode* node, vector<int>& path) -> void {
            if (!node->left && !node->right) 
                if (accumulate(path.begin(), path.end(), 0)==targetSum) ans.push_back(path);
            if (node->left) {
                path.push_back(node->left->val);
                dfs(node->left, path);
                path.pop_back();
            }
            if (node->right) {
                path.push_back(node->right->val);
                dfs(node->right, path);
                path.pop_back();
            }
        };
        vector<int> path{root->val};
        dfs(root, path);
        
        return ans;            
    }
};