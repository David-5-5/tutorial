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
    int sumEvenGrandparent(TreeNode* root) {
        // 自行解答
        auto dfs = [](this auto&& dfs, TreeNode* node, TreeNode* grandp) -> int {
            if (!node) return 0;
            int res = 0;
            if (node->left) res += ((grandp && grandp->val%2==0)? node->left->val:0) + dfs(node->left, node);
            if (node->right) res += ((grandp && grandp->val%2==0)? node->right->val:0) + dfs(node->right, node);
            return res;
        };
        return dfs(root, nullptr);
    }
};