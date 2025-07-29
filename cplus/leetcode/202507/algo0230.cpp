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
    int kthSmallest(TreeNode* root, int k) {
        // 自行解答
        int ans = 0;
        auto find = [&](this auto&& find, TreeNode* node) -> void {
            if (!node) return;
            find(node->left); 
            if (k == 1) ans = node->val;
            k--;
            find(node->right);
        };

        find(root);
        return ans;        
    }
};