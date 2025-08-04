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
    int findBottomLeftValue(TreeNode* root) {
        // 自行解答
        vector<TreeNode*> cur;
        cur.push_back(root); int ans;
        while (!cur.empty()) {
            ans = cur[0]->val;
            vector<TreeNode*> nxt;
            for (auto node:cur) {
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            cur = move(nxt);
        }
        return ans;
    }
};