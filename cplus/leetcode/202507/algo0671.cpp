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
    int findSecondMinimumValue(TreeNode* root) {

        auto dfs = [&](this auto&& dfs, TreeNode* node) -> int {

            if (!node->left && !node->right)  return node->val;

            auto left = dfs(node->left);
            auto right = dfs(node->right);
            return min(left, right) == root->val?max(left, right):min(left, right);
        };

        auto ans = dfs(root);
        
        return ans==root->val?-1:ans;
    }
};