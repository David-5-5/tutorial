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

// 二叉树 - 2.5 有递有归
class Solution {
public:
    TreeNode* bstToGst(TreeNode* root) {
        auto dfs = [&] (this auto&& dfs, TreeNode* node, int gr) -> int {
            
            int res = node->val, right = 0, left = 0;
            if(node->right) right = dfs(node->right, gr);
            node->val += right + gr;
            if (node->left)  {
               left = dfs(node->left, node->val);
            } 
            return res + right + left;
        };
        dfs(root, 0);
        return root;        
    }

    int sum = 0;
    TreeNode* bstToGst(TreeNode* root) {
        // 参考题解
        if (root) {
            bstToGst(root->right);
            sum += root->val;
            root->val = sum;
            bstToGst(root->left);
        }
        
        return root; 
    }
};