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

// 二叉树 - 2.11 插入/删除节点
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        // 参考题解
        if (!root) return nullptr;

        if (root->val > key) {
            root->left = deleteNode(root->left, key);
            return root;
        }
        if (root->val < key) {
            root->right = deleteNode(root->right, key);
            return root;
        }
        auto merge = [&](this auto&& merge, TreeNode* root, TreeNode* node) -> TreeNode* {
            if (!root) return node;
            if (root->val > node->val) {
                root->left = merge(root->left, node);
            } else root->right = merge(root->right, node);
            return root;
        };

        if (root->val == key) {
            if (!root->left && !root->right) return nullptr; // 左右子结点都为null
            if (root->left && root->right) {    // 左右子结点都不为 null
                return merge(root->right, root->left);
            }
            if (root->left) return root->left;
            if (root->right) return root->right;
        }
        return root;
    }
};