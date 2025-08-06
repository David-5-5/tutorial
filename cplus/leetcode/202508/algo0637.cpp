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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<TreeNode*> cur;
        if (root) cur.push_back(root); vector<double> ans;
        while (!cur.empty()) {
            double sum = 0;
            vector<TreeNode*> nxt;
            for (auto node:cur) {
                sum += node->val;
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            ans.push_back(sum/cur.size()); cur = move(nxt); 
        }
        return ans;              
    }
};