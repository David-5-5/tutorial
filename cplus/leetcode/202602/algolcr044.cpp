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

// 同 515
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<TreeNode*> cur;
        if (root) cur.push_back(root); vector<int> ans;
        while (!cur.empty()) {
            auto mx = cur[0]->val;
            vector<TreeNode*> nxt;
            for (auto node:cur) {
                mx = max(mx, node->val);
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            cur = move(nxt); ans.push_back(mx);
        }
        return ans;        
    }
};