#include <bits/stdc++.h>
using namespace std;

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
    vector<vector<int>> BSTSequences(TreeNode* root) {
        if (root == nullptr) return {{}};

        auto weave = [](vector<int>& a, vector<int> b) -> vector<vector<int>> {
            vector<vector<int>> res;
            vector<int> path;
            auto backtrack = [&](this auto&& bk, int i, int j) -> void {
                if (i == a.size() && j == b.size()) res.emplace_back(path);

                if (i < a.size()) {
                    path.emplace_back(a[i]);
                    bk(i+1, j);
                    path.pop_back();
                }
                if (j < b.size()) {
                    path.emplace_back(b[j]);
                    bk(i, j+1);
                    path.pop_back();
                }
            };

            backtrack(0, 0);
            return res;
        };

        auto left = BSTSequences(root->left);
        auto right = BSTSequences(root->right);

        vector<vector<int>> ans;

        for (auto l : left) for (auto r: right) {
            auto ws = weave(l, r);
            for (auto & w: ws) {
                vector<int> res = {root->val};
                res.insert(res.end(), w.begin(), w.end());
                ans.emplace_back(res);
            }
        }

        return ans;
    }
};