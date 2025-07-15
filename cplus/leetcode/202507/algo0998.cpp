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
    string smallestFromLeaf(TreeNode* root) {
        //  参考题解 - 字符串的比较，倒置，复制，对象引用
        string ans = "~";
        auto dfs = [&](this auto&& dfs, TreeNode* node, string& curr) -> void {
            // if (!node) return;
            
            curr.push_back('a' + node->val);    // 加入当前节点字符
            if (!node->left && !node->right) {  // 递归边界
                string leaf = curr;
                reverse(leaf.begin(), leaf.end());
                ans = min(ans, leaf);
            }
            if (node->left) dfs(node->left, curr);
            if (node->right) dfs(node->right, curr);
            curr.pop_back();                // 回溯，恢复现场
        };
        string curr = "";
        dfs(root, curr);
        return ans;
    }
}; 