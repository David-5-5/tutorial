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
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> nums;

        auto traverse = [&] (this auto&& traverse, TreeNode* node) -> void {
            if (!node) return;
            traverse(node->left);
            nums.push_back(node->val);
            traverse(node->right);
        };

        traverse(root);

        auto dfs = [&](this auto&& dfs, int l, int r) -> TreeNode* {
            if (l > r) return nullptr;
            int mid = l + (r - l)/2;
            return new TreeNode(nums[mid], dfs(l, mid-1), dfs(mid+1, r));
        };
        return dfs(0, nums.size()-1);        
    }
};