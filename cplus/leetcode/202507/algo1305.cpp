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
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        // 自行解答，暴力
        vector<int> ans;
        auto dfs = [&] (this auto&& dfs, TreeNode* node) -> void {
            if (!node) return;
            ans.push_back(node->val);
            dfs(node->left); dfs(node->right);
        };
        dfs(root1); dfs(root2);
        sort(ans.begin(), ans.end()); return ans;
    }

    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        // 参考题解中序遍历 + 归并
        vector<int> nums1, nums2;
        auto dfs = [&](this auto&& dfs, TreeNode* node, vector<int>& arr) -> void {
            if (!node) return;
            dfs(node->left, arr); arr.push_back(node->val); dfs(node->right, arr);
        };

        dfs(root1, nums1); dfs(root2, nums2);

        vector<int> merged;
        int p1 = 0, p2 = 0;
        while (p1 < nums1.size() || p2 < nums2.size()) {
            if (p1 < nums1.size() && p2 < nums2.size()) {
                if (nums1[p1] < nums2[p2]) 
                    merged.push_back(nums1[p1++]);
                else merged.push_back(nums2[p2++]);
            } else if (p1 < nums1.size()) merged.push_back(nums1[p1++]);
            else if (p2 < nums2.size()) merged.push_back(nums2[p2++]);
        }
        return merged;
    }    
};