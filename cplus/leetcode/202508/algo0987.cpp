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

// 二叉树 - 2.16 其他
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // 自行解答
        map<int, vector<pair<int, int>>> mp;
        auto dfs = [&] (this auto&& dfs, TreeNode* node, int row, int col) -> void {
            mp[col].emplace_back(row, node->val);
            if (node->left) dfs(node->left, row+1, col-1);
            if (node->right) dfs(node->right,row+1, col+1);
        };

        dfs(root, 0, 0);
        
        vector<vector<int>> ans;
        for (auto [_, v]: mp) {
            sort(v.begin(), v.end());
            vector<int> row;
            for (auto& [_, val]: v) row.push_back(val);
            ans.push_back(row);
        }

        return ans;

    }
};