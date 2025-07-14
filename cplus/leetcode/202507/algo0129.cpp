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

// 二叉树 - 2.2 自顶向下 DFS
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        // 自行解答，用BFS
        int ans = 0;
        deque<pair<TreeNode*,int>> q; q.push_back({root, 0});
        while (!q.empty()) {
            auto [node, pre] = q.front();  q.pop_front();
            auto cur = pre*10 + node->val;
            if (!node->left && !node->right) ans += cur;
            if (node->left) q.push_back({node->left, pre*10 + node->val});
            if (node->right) q.push_back({node->right, pre*10 + node->val});
        }
        return ans;
    }
};