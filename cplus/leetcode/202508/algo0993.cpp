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

// 二叉树 - 2.13 二叉树 BFS
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        
        if (root->val == x || root->val == y) return false;
        int depth = 0, x_depth = 0, y_depth = 0, x_fa = 0, y_fa = 0;

        vector<TreeNode*> cur; cur.push_back(root);
        while (!cur.empty()) {
            depth ++;
            vector<TreeNode*> nxt;
            for (auto& node:cur) {
                if (node->left) {
                    nxt.push_back(node->left);
                    if (node->left->val == x) {x_depth = depth; x_fa = node->val;}
                    if (node->left->val == y) {y_depth = depth; y_fa = node->val;}
                }
                if (node->right) {
                    nxt.push_back(node->right);
                    if (node->right->val == x) {x_depth = depth; x_fa = node->val;}
                    if (node->right->val == y) {y_depth = depth; y_fa = node->val;}
                }
            }
            if (x_depth || y_depth) break;
            cur = move(nxt);
        }        
        return x_depth == y_depth && x_fa!=y_fa;    
    }
};