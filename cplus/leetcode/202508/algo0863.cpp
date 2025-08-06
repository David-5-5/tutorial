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
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        // 先深度找到节点的父节点，再从target出发，广度优先搜索，找到距离为 k 的节点
        unordered_map<TreeNode*, TreeNode*> fa;
        unordered_map<TreeNode*, bool> vis;

        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            vis[node] = false;
            if (node->left) {fa[node->left] = node; dfs(node->left);}
            if (node->right) {fa[node->right] = node;dfs(node->right);}
        };
        dfs(root);
        vector<TreeNode*> q; vector<int> ans; int l = 0;
        q.push_back(target); vis[target] = true;
        while (!q.empty() && l < k) {
            l++;
            vector<TreeNode*> nxt;
            for (auto& node:q) {
                if (node->left && !vis[node->left]) {
                    vis[node->left] = true; nxt.push_back(node->left);
                }
                if (node->right && !vis[node->right]) {
                    vis[node->right] = true; nxt.push_back(node->right);
                }
                if (fa.count(node) && !vis[fa[node]]) {
                    vis[fa[node]] = true; nxt.push_back(fa[node]);
                }                
            }
            q = move(nxt);
        }

        for (auto node:q) ans.push_back(node->val);
        return ans;
    }
};