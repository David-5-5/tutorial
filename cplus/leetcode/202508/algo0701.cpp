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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // 自行解答
        if (root == nullptr) return new TreeNode(val);

        if (root->val > val) {
            root->left = insertIntoBST(root->left, val);
        } else root->right = insertIntoBST(root->right, val);

        return root;     
    }
};