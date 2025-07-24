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
    int averageOfSubtree(TreeNode* root) {
        // 自行解答
        int ans = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> pair<int, int> {
            if (!node->left && !node->right) {
                ans += 1; return {node->val, 1};
            }
            int sum = node->val, cnt = 1;
            if (node->left) {
                auto [s, c] = dfs(node->left);
                sum += s, cnt += c;
            }
            if (node->right) {
                auto [s, c] = dfs(node->right);
                sum += s, cnt += c;
            } 
            if (node->val == sum/cnt) ans ++;
            return {sum, cnt};
        };

        dfs(root);
        return ans;   
    }
};