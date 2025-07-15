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
    int pseudoPalindromicPaths (TreeNode* root) {
        // 自行解答 + 直接用位运算优化
        auto dfs = [&](this auto&& dfs, TreeNode* node, int mask) -> int{
            if (!node->left && !node->right) return mask == 0 || (mask&(mask-1)) == 0;
            int res = 0;
            if (node->left) res += dfs(node->left, mask ^ (1<<node->left->val));
            if (node->right) res += dfs(node->right, mask ^ (1<<node->right->val));
            return res;
        };

        return dfs(root, 1<<root->val);
    }
};