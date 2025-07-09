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
    vector<int> rightSideView(TreeNode* root) {
        // 按dfs 中序遍历，按照深度更新结果，同一深度，最后出现的就是右视图
        vector<int> ans;
        if (root == nullptr) return ans;
        auto dfs = [&](this auto&& dfs, TreeNode* node, int d) -> void {
            if (d<ans.size()) ans[d] = node->val;
            else ans.push_back(node->val);
            if (node->left) dfs(node->left, d+1);
            if (node->right) dfs(node->right, d+1);
        };

        dfs(root, 0);
        return ans;
    }
};