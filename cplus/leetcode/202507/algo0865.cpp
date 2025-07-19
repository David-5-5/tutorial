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

// 二叉树 - 2.5 有递有归
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        // 自行解答
        set<int> mx_nodes; int mx_d = 0;
        auto depth = [&](this auto&& depth, TreeNode* node, int d) -> void {
            if (!node) return;
            if (d > mx_d) {mx_nodes.clear(), mx_d = d;}
            if (d == mx_d) mx_nodes.insert(node->val);
            depth(node->left, d+1);
            depth(node->right, d+1);
        };
        depth(root, 0);

        TreeNode* ans = nullptr;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> int {
            if (!node) return 0;
            int res = mx_nodes.count(node->val)?1:0;
            res += dfs(node->left);
            res += dfs(node->right);
            if (res == mx_nodes.size()) {cout << mx_nodes.size() << endl; ans = node; return 0;}
            return res;
        };

        dfs(root);
        return ans;
    }

    
};