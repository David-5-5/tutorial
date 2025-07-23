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
    bool isValidBST(TreeNode* root) {
        // 自行解答 - 不是很优雅
        bool valid = true;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> pair<int, int> {
            if (!valid) return  {INT_MAX, 0};
            if (!node->left && !node->right) return {node->val, node->val};
            pair res = {node->val, node->val};
            if (node->left) {
                auto left = dfs(node->left);
                if (node->val <= left.second) {
                    valid = false; return {INT_MAX, 0};
                } else {
                    res.first= min(res.first, left.first); res.second = max(res.second, left.second);
                }
            }   
            if (node->right) {
                auto right = dfs(node->right);
                if (node->val >= right.first) {
                    valid = false; return {INT_MAX, 0};
                } else {
                    res.first= min(res.first, right.first); res.second = max(res.second, right.second);
                }
            }
            return res;
        };
        dfs(root);
        return valid;  
    }

    bool isValidBST(TreeNode* root, long left=LONG_MIN, long right=LONG_MAX) {
        // 参考题解 前序遍历
        if (!root) return true;
        auto x = root->val;
        return x > left && x < right && isValidBST(root->left, left, x) && isValidBST(root->right, x, right);
    }

    long pre = LONG_MIN; 
    bool isValidBST(TreeNode* root) {
        // 参考题解 中序遍历
        if (!root) return true;
        if (!isValidBST(root->left)) return false;
        if (root->val <= pre) return false;
        pre = root->val;
        return isValidBST(root->right);
    } 

    bool isValidBST(TreeNode* root) {
        // 参考题解，后序遍历，我的解法类似后续，但没有这个优雅
        auto dfs = [&] (this auto&& dfs, TreeNode* node) ->pair<long, long> {
            if (node == nullptr) {
                return {LLONG_MAX, LLONG_MIN};
            }
            auto[l_min, l_max] = dfs(node->left);
            auto[r_min, r_max] = dfs(node->right);
            long x = node->val;
            // 也可以在递归完左子树之后立刻判断，如果发现不是二叉搜索树，就不用递归右子树了
            if (x <= l_max || x >= r_min) {
                return {LLONG_MIN, LLONG_MAX};
            }
            return {min(l_min, x), max(r_max, x)};
        };
        return dfs(root).second!=LONG_MAX;
    }


};