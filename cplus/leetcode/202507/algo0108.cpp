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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 参考题解，递归实现 ：取 mid 为根节点，[l,mid-1] [mid+1,r] 为左右子节点
        int n = nums.size();
        auto dfs = [&](this auto&& dfs, int l, int r) -> TreeNode* {
            if (l > r) return nullptr;
            int mid = l + (r - l)/2;
            return new TreeNode(nums[mid], dfs(l, mid-1), dfs(mid+1, r));
        };
        return dfs(0, n-1);
    }
};