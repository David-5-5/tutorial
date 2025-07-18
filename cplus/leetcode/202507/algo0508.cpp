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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        int mx_cnt = 0;
        unordered_map<int, int> cnt;
        auto dfs = [&] (this auto&& dfs, TreeNode* node) -> int {
            int sum = node->val;
            if (node->left) sum += dfs(node->left);
            if (node->right) sum += dfs(node->right);
            cnt[sum] += 1; mx_cnt = max(mx_cnt, cnt[sum]);
            return sum;
        };

        dfs(root);
        vector<int> ans;
        for (auto &[k, v] : cnt) {
            if (v == mx_cnt) ans.push_back(k);
        }
        return ans;

    }
};