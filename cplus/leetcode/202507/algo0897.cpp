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
    TreeNode* increasingBST(TreeNode* root) {
        // 自行解答
        TreeNode *new_root = nullptr, *tail = nullptr;
        auto dfs = [&] (this auto&& dfs, TreeNode* node)->void {
            if (!node) return;
            dfs(node->left);
            if (new_root == nullptr) {
                new_root = node; tail = node; 
            } else {
                tail->right = node; tail = node;
            }
            tail->left = nullptr;
            dfs(node->right);
        };
        dfs(root);
        return new_root;        
    }
};