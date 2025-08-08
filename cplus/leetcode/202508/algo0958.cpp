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
    bool isCompleteTree(TreeNode* root) {
        bool finishd = false;
        vector<TreeNode*> cur; cur.push_back(root);
        while (!cur.empty()) {
            vector<TreeNode*> nxt;
            for (auto& node:cur) {
                if (node->left) {if (finishd) return false; nxt.push_back(node->left);}
                else finishd = true;
                if (node->right) {if (finishd) return false; nxt.push_back(node->right);}
                else finishd = true;
            }
            cur = move(nxt);
        }

        return true;
    }
};