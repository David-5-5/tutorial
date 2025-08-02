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

// 二叉树 - 2.10 创建二叉树
class Solution {
public:
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        // 自行解答
        if (val > root->val) {
            auto tmp = root->val; root->val = val;      // 避免 fa pointer，替换 root 的值
            auto cur = new TreeNode(tmp, root->left, root->right);
            root->left = cur; root->right = nullptr;
        } else {
            if (root->right) insertIntoMaxTree(root->right, val);
            else root->right = new TreeNode(val);
        }

        return root;
    }
};