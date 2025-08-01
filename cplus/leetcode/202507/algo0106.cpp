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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        unordered_map<int, int> in_pos;
        for (int i=0; i<n; i++) in_pos[inorder[i]] = i;

        auto dfs = [&](this auto&& dfs, int post_l, int post_r, int in_l, int in_r) -> TreeNode* {
            if (post_l > post_r) return nullptr;
            auto in_root = in_pos[postorder[post_r]];
            auto len_l = in_root - in_l; // , len_r = in_r - in_root
            return new TreeNode(postorder[post_r],
                        dfs(post_l,post_l+len_l-1,in_l,in_root-1),     // 细心
                        dfs(post_l+len_l, post_r-1, in_root+1, in_r));
        };
        
        return dfs(0, n-1, 0, n-1);
    }
};