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
    int longestZigZag(TreeNode* root) {
        int ans = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* node, int p, int l) -> void {
            ans = max(ans, l);
            if (node->left) dfs(node->left, 0, p==0?1:l+1);
            if (node->right) dfs(node->right, 1, p==1?1:l+1);
        };

        dfs(root, -1, 0);
        return ans;
    }
};