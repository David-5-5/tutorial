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

// 二叉树 - 2.4 自底向上 DFS：删点
class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        // 自行解答
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> bool {
            if (node->left && dfs(node->left))  node->left = nullptr;
            if (node->right && dfs(node->right)) node->right = nullptr;

            if (!node->left && !node->right) return node->val==target;
            else return false;
        };

        auto cnt = dfs(root);
        return cnt?nullptr:root;
    }


};