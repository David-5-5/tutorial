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

// 二叉树 - 2.9 二叉搜索树
class Solution {
public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        vector<int> a;

        auto dfs  = [&] (this auto&& dfs, TreeNode *node) {
            if (node == nullptr) {
                return;
            }
            dfs(node->left);
            a.push_back(node->val);
            dfs(node->right);
        };

        dfs(root);
        int n = a.size();
        vector<vector<int>> ans;
        for (int q : queries) {
            int j = ranges::lower_bound(a, q) - a.begin();
            int mx = j < n ? a[j] : -1;
            if (j == n || a[j] != q) { // a[j]>q, a[j-1]<q
                j--;
            }
            int mn = j >= 0 ? a[j] : -1;
            ans.push_back({mn, mx});
        }
        return ans;
    }
};