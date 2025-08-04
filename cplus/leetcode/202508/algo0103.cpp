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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        // 自行解答
        vector<vector<int>> ans;
        vector<TreeNode*> cur; if(root) cur.push_back(root);
        int even = 0;
        while (!cur.empty()) {
            vector<TreeNode*> nxt;
            vector<int> res;
            for (auto node: cur) {
                res.push_back(node->val);
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            if (even) reverse(res.begin(), res.end());
            even ^= 1;
            ans.push_back(res); cur = move(nxt);
        }

        return ans;
    }
};