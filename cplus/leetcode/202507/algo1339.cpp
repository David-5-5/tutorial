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
    int maxProduct(TreeNode* root) {
        // 自行解答
        const int mod = 1e9 + 7;

        int sum = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            sum += node->val;
            if (node->left) dfs(node->left);
            if (node->right) dfs(node->right);
        };
        dfs(root);

        long long ans = 0;
        auto cal = [&](this auto&& cal, TreeNode* node) -> int {
            int sub_sum = node->val;
            if (node->left)  sub_sum += cal(node->left);
            if (node->right) sub_sum += cal(node->right);
            ans = max(ans, (long long)sub_sum * (sum-sub_sum));
            return sub_sum;
        };

        cal(root);
        return ans % mod;
    }

    int maxProduct2(TreeNode* root) {
        // 参考题解
        const int mod = 1e9 + 7;

        int sum = 0; 
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
            sum += node->val;
            if (node->left) dfs(node->left);
            if (node->right) dfs(node->right);
        };
        dfs(root);

        int best = sum; // best == sum/2
        auto dfs2 = [&](this auto&& dfs2, TreeNode* node) -> int {
            int res = node->val;
            if (node->left)  res += dfs2(node->left);
            if (node->right) res += dfs2(node->right);
            if (abs(res * 2 - sum) < abs(best*2-sum)) best = res;
            return res;
        };

        dfs2(root);
        return ((long long)best * (sum-best)) % mod;
    }    
};