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
        // 自行解答 - dfs
        int cnt[10] = {};

        auto dfs = [&] (this auto&& dfs, TreeNode* node) -> int {
            if (!node->left && !node->right) return 0;
            if (node->left && node->right) {
                auto left = dfs(node->left), right = dfs(node->right);
                if (left == -1 || right == -1 || left != right) return -1;
                cnt[1+left] ++;
            } else return -1;
        };
        dfs(root);
        for (int i=9; i>0; i--) {
            auto c = cnt[i];
            if (c >= k) return (1 << i) - 1;
            k -= c;
        }
        return -1;
    }
};