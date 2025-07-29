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

// 二叉树 - 2.8 最近公共祖先
class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        // 同 865
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> pair<TreeNode*, int> {
            if (!node) return {node, 0};
            
            auto left  = dfs(node->left);
            auto right = dfs(node->right);
            
            if (left.second == right.second)
                return {node, left.second+1};
            else if (left.second > right.second)
                return {left.first, left.second+1};
            else return {right.first, right.second+1};

        };

        return dfs(root).first;           
    }
};