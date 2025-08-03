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

// 二叉树 - 2.10 创建二叉树
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> mp;
        unordered_map<int, int> degree;
        for (auto desc : descriptions) {
            auto pa = desc[0], ch = desc[1], isLeft = desc[2];
            if (!mp.count(pa)) {
                mp[pa] = new TreeNode(pa); degree[pa] = 0;
            }
            if (!mp.count(ch)) {
                mp[ch] = new TreeNode(ch); degree[ch] = 0;
            }
            if (isLeft == 1) mp[pa]->left = mp[ch];
            else mp[pa]->right = mp[ch];
            degree[ch] ++;
        }
        for (auto &[k, v]: degree) if (v == 0) return mp[k];
        return nullptr;
    }
};