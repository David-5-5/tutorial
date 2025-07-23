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

// 二叉树 - 2.9 二叉搜索树
class Solution {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        // 自行解答，暴力
        vector<int> ans;
        auto dfs = [&] (this auto&& dfs, TreeNode* node) -> void {
            if (!node) return;
            ans.push_back(node->val);
            dfs(node->left); dfs(node->right);
        };
        dfs(root1); dfs(root2);
        sort(ans.begin(), ans.end()); return ans;
    }


};