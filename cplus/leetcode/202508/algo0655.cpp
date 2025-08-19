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

// 二叉树 - 2.16 其他
class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
        // 自行解答
        auto depth = [](this auto&& f, TreeNode* node) -> int {
            if (!node) return 0;
            return max(f(node->left), f(node->right)) + 1;
        };
        int m = depth(root); int n = (1 << m) - 1;
        int r = 0, c = (n-1) / 2;

        vector<vector<string>> ans(m, vector<string>(n, ""));
        auto dfs = [&](this auto&& f, TreeNode* node, int r, int c) -> void {
            ans[r][c] = to_string(node->val);
            if (r == m-1) return;   
            auto offset = 1<<(m-2-r);   // 不判断 r， m-2-r会小于0
            if (node->left) f(node->left, r+1, c - offset);
            if (node->right) f(node->right, r+1, c + offset);
        };
        dfs(root, r, c);
        return ans;
             
    }
};