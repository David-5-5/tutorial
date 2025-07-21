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

// 二叉树 - 2.3 自底向上 DFS
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {

        auto isSub = [&](this auto&& isSub, TreeNode* node, TreeNode* subNode) -> bool {
            if (node->val != subNode->val) return false;
            if ((node->left && !subNode->left) || (!node->left && subNode->left) ||
                (node->right && !subNode->right) || (!node->right && subNode->right))
                return false; 
            if (node->left && subNode->left && !isSub(node->left, subNode->left)) return false;
            if (node->right && subNode->right && !isSub(node->right, subNode->right)) return false;
            
            return true;
        };

        auto dfs = [&](this auto&& dfs, TreeNode* node) -> bool {
            if (isSub(node, subRoot)) return true;
            if (node->left && dfs(node->left)) return true;
            if (node->right && dfs(node->right)) return true;

            return false;
        };
        return dfs(root);
    }
};