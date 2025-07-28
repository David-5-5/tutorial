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

// 二叉树 - 2.7 回溯
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        // 自行解答
        unordered_map<long, int> cnt;

        auto dfs = [&](this auto&& dfs, TreeNode* node, long sum) -> int {
            if (!node) return 0;
            sum += node->val;
            auto res = cnt[sum-targetSum];
            cnt[sum] ++;
            res += dfs(node->left, sum); res += dfs(node->right, sum);
            cnt[sum] --;
            return res;
        };

        cnt[0] = 1;
        return dfs(root, 0);  
        
    }
};