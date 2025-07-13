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
    int sumOfLeftLeaves(TreeNode* root) {
        // 自行解答
        auto is_leaf = [] (TreeNode* node) -> bool {
            if (!node) return false;

            return !node->left && !node->right;
        };

        auto dfs = [&] (this auto&& dfs, TreeNode* node) -> int {
            int res = 0;
            if (!node) return 0;
            res += is_leaf(node->left)? node->left->val : dfs(node->left); 

            res += dfs(node->right);
            return res;
        };        

        return dfs(root);
    }
};