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
    // 两数之和 
    unordered_set<int> vis;
    bool findTarget(TreeNode* root, int k) {
        
        if (!root) return false;
        if (vis.count(k - root->val)) return true;
        vis.insert(root->val);
        return findTarget(root->left, k) || findTarget(root->right, k);
    }
};