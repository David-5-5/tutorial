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
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        // 参考题解
        vector<TreeNode*> ans;
        set<int> to_del(to_delete.begin(), to_delete.end());

        auto dfs = [&](this auto&& dfs, TreeNode* node, bool is_root) -> TreeNode* {
            if (!node) return nullptr;
            
            
            bool deleted = to_del.count(node->val) ? true : false;
            node->left = dfs(node->left, deleted);
            node->right = dfs(node->right, deleted);
            if (deleted) return nullptr;
            else {
                if (is_root) ans.emplace_back(node);
                return node;
            }
        };

        dfs(root, true);
        return ans;
    }
};
