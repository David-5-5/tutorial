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

// 二叉树 - 2.2 自顶向下 DFS
class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        // 自行解答
        int ans = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* node, int pre){
            int cur = (pre<<1) + node->val;         // 优先级

            if (!node->left && !node->right) {
                ans += cur;
                return;
            }
            
            if (node->left) dfs(node->left, cur);
            if (node->right) dfs(node->right, cur);
        };

        dfs(root, 0);
        return ans;   
    }
};