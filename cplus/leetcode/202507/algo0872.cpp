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

// 二叉树 - 2.1 遍历二叉树 
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        // 自行解答
        auto dfs = [&] (this auto&& dfs, TreeNode* node, vector<int>& leaf) -> void {
            if (node->left == nullptr && node->right == nullptr) {
                leaf.push_back(node->val);
                return;
            }
            if (node->left) dfs(node->left, leaf);
            if (node->right) dfs(node->right, leaf);
        };

        vector<int> ans1, ans2;
        dfs(root1, ans1); dfs(root2, ans2);

        // if (ans1.size() != ans2.size()) return false;
        // for (int i=0; i < ans1.size(); ++i) if (ans1[i] != ans2[i]) return false;
        // return true;
        return ans1 == ans2;
    }
};