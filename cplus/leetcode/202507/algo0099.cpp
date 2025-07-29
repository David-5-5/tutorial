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
    void recoverTree(TreeNode* root) {
        // 中序遍历
        TreeNode* a = nullptr, *b = nullptr, * last = nullptr;

        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            if (!node) return;
            dfs(node->left);
            if (last!=nullptr && last->val > node->val) {
                if (a == nullptr) a = last, b = node;
                else b = node;
            }
            last = node;
            dfs(node->right);
        };

        dfs(root);
        auto val = a->val;
        a->val = b->val; b->val = val;
    }
};