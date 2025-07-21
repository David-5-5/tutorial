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

// 二叉树 - 2.3 自底向上 DFS
class Solution {
public:
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        // 参考题解，计算左右子树高度
        int cnt[10] = {};

        auto dfs = [&] (this auto&& dfs, TreeNode* node) -> int {
            if (!node->left && !node->right) { cnt[0] ++; return 0;};   // 叶子节点，高度为 0
            int left = -1, right = -1;
            if (node->left) left = dfs(node->left);
            if (node->right) right = dfs(node->right);
            if (left == -1 || right == -1 || left != right) return -1;  // 左右节点不是完美子树或高度不相等
            cnt[1+left] ++; return 1 + left;                            // 完美子树，记录高度
        };
        dfs(root);
        for (int i=9; i>=0; i--) {
            auto c = cnt[i];
            if (c >= k) return (1 << (i+1)) - 1;
            k -= c;
        }
        return -1;        
    }
};