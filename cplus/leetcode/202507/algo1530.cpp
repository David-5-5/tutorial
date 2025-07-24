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
    int countPairs(TreeNode* root, int distance) {
        // 自行解答 - dfs
        int ans = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> vector<int> {
            if (!node) return {};
            if (!node->left && !node->right) return {1};
            auto left = dfs(node->left), right = dfs(node->right);
            for (int i=0; i<left.size(); i++) for (int j=0; j<right.size(); ++j){
                if (i+j+2 <= distance) ans += left[i] * right[j];
            }
            int len = min(distance, (int)max(left.size(), right.size())+1) ;
            vector<int> ans(len);
            for (int i=0; i<min(len-1, (int)left.size()); ++i) ans[i+1] += left[i];
            for (int i=0; i<min(len-1, (int)right.size()); ++i) ans[i+1] += right[i];
            return ans;
        };

        dfs(root);
        return ans;
    }
};