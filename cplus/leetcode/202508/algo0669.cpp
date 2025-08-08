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
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (!root) return nullptr;

        if (root->val >= low && root->val <= high) {
            root->left = trimBST(root->left, low, high);
            root->right = trimBST(root->right, low, high);
        } else { // root.val < low || root.val > high
            // 下式仅有一个有效
            if (root->val >= low) return trimBST(root->left, low, high);            // root.val > high， right更大
            else if (root->val <= high) return trimBST(root->right, low, high);     // root.val < low， left更小
            else return nullptr;
        }
        return root;
    }
};