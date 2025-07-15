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
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> ans;
        int inx = 0;
        
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            if (node == nullptr) return;
            if (node->val != voyage[inx]) {
                ans.clear(); ans.push_back(-1); return;
            } 
            inx ++;
            if (inx < voyage.size() && node->left and node->left->val!=voyage[inx]) {
                ans.push_back(node->val);
                dfs(node->right); dfs(node->left);
            } else {
                dfs(node->left); dfs(node->right); 
            }
        };

        dfs(root);
        if (ans.size() && ans[0]==-1) return {-1}; else return ans;
    }
};