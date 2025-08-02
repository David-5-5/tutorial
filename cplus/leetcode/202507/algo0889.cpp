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

// 二叉树 - 2.10 创建二叉树
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = postorder.size();
        unordered_map<int, int> post_pos;
        for (int i=0; i<n; i++) post_pos[postorder[i]] = i;

        auto dfs = [&](this auto&& dfs, int pre_l, int pre_r, int post_l, int post_r) -> TreeNode* {
            if (pre_l > pre_r) return nullptr;
            if (pre_l == pre_r) return new TreeNode(preorder[pre_l]);

            auto left_root = post_pos[preorder[pre_l+1]];
            auto len_l = left_root - post_l + 1; // , len_r = in_r - in_root
            return new TreeNode(preorder[pre_l],
                        dfs(pre_l+1, pre_l+len_l, post_l, left_root),     // 细心
                        dfs(pre_l+len_l+1, pre_r, left_root+1, post_r-1));
        };
        
        return dfs(0, n-1, 0, n-1);        
    }
};