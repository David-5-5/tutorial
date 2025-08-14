#include <bits/stdc++.h>
using namespace std;


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 二叉树 - 2.16 其他
class Solution {
public:
    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
        vector<int> nums;
        auto inorder = [&](this auto&& inorder, TreeNode* node) -> void {
            if (!node) return;
            inorder(node->left);
            nums.push_back(node->val);
            inorder(node->right);
        };
        inorder(root);
        int n = nums.size();
        // 参考 oi-wiki 线段树模板 - 区间更新 最大值
        vector<int> tree(4 * n);
        vector<int> tp(4 * n);     // 支持懒标记

        // 下推懒标记
        auto pushdown = [&] (this auto&& pushdown, int s, int t, int p) -> void{
            if (s == t) return;  // 叶子节点无需下推
            int m = s + ((t - s) >> 1);

            // 更新左子树
            tree[p * 2 + 1] = tp[p]==1?m-s+1:0; tp[p * 2 + 1] = tp[p];
            // 更新右子树
            tree[p * 2 + 2] = tp[p]==1?t-m:0; tp[p * 2 + 2] = tp[p];
            // 清空当前节点懒标记
            tp[p] = 0;
        };

        // 区间更新：[l, r] 区间增加 value
        auto update = [&](this auto&& update, int l, int r, int value, int s, int t, int p) -> void{
            if (l <= s && t <= r) {
                // 当前区间完全在更新范围内
                tree[p] = value==1?t-s+1:0; // 区间 + val
                if (s != t)  tp[p] = value; // 非叶子节点才需要标记
                return;
            }
            // 下推懒标记
            if (tp[p] != 0) pushdown(s, t, p);

            int m = s + ((t - s) >> 1);
            // 递归更新左子树
            if (l <= m)  update(l, r, value, s, m, p * 2 + 1);
            // 递归更新右子树
            if (r > m) update(l, r, value, m + 1, t, p * 2 + 2);
            // 更新当前节点值
            tree[p] = tree[p * 2 + 1] + tree[p * 2 + 2];
        };

        for (auto& op:ops) {
            auto t = op[0], left = op[1], right = op[2];
            int l = ranges::lower_bound(nums, left) - nums.begin();
            int r = ranges::lower_bound(nums, right) - nums.begin();
            if (t == 1)
                update(l, r, 1, 0, n-1, 0);
            else
                update(l, r, -1, 0, n-1, 0);
        }
        return tree[0];
    } 
};