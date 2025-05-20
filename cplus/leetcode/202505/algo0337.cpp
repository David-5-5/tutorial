#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.2 树上最大独立集

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int rob(TreeNode* root) {   
        // 自行解答， 记忆化搜索

        // 使用对象情况下的记忆化
        unordered_map<TreeNode*, int> select, unselect;

        auto dfs = [&] (this auto&& dfs, TreeNode* node, bool f) -> int {
            if (node == nullptr) return 0;

            if (f && select.count(node)) return select[node];
            if (!f && unselect.count(node)) return unselect[node];

            int res = dfs(node->left, false) + dfs(node->right, false);
            if (!f)
                res = max(res, node->val + dfs(node->left, true) + dfs(node->right, true));
            
            if (f) select[node] = res;
            else unselect[node] = res;
            
            return res;
        };
        return dfs(root, false);  
    }
};