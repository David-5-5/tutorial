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
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        // 自行解答
        if (depth == 1) return new TreeNode(val, root, nullptr);

        auto dfs = [&] (this auto&& dfs, TreeNode* node, int d) -> void {
            if (d == depth -1) {
                node->left = new TreeNode(val, node->left, nullptr);
                node->right = new TreeNode(val, nullptr, node->right);
                return;
            }

            if (node->left) dfs(node->left, d+1);
            if (node->right) dfs(node->right, d+1);
        };
        dfs(root, 1);
        return root;
    }
};