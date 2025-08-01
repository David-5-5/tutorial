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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // 自行解答
        int n = inorder.size();
        unordered_map<int, int> in_pos;
        for (int i=0; i<n; i++) in_pos[inorder[i]] = i;

        auto dfs = [&](this auto&& dfs, int pre_l, int pre_r, int in_l, int in_r) -> TreeNode* {
            if (pre_l > pre_r) return nullptr;
            auto in_root = in_pos[preorder[pre_l]];
            auto len_l = in_root - in_l; // , len_r = in_r - in_root
            return new TreeNode(preorder[pre_l],
                        dfs(pre_l+1,pre_l+len_l,in_l,in_root-1),     // 细心
                        dfs(pre_l+1+len_l, pre_r, in_root+1, in_r));
        };
        
        return dfs(0, n-1, 0, n-1);
    }
};