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

// 二叉树 - 2.8 最近公共祖先
class Solution {
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        // 自行解答 代码不够优雅
        // 求出接点的 LCA
        auto lca = [&] (this auto&& dfs, TreeNode* node) -> TreeNode* {
            if (!node || node->val == startValue || node->val == destValue) return node;
            auto lson = dfs(node->left);
            auto rson = dfs(node->right);
            if (lson && rson) return node;
            return lson?lson:rson;
        };

        // 回溯求出 lca 到 子节点的路径 L R 表示
        // 力扣s题解在求lca时，求出了每个节点的parent，因此从 startValue 和 destValue 节点可找 lca 节点
        string lca2dest = "";
        auto dfs = [&](this auto&& dfs, TreeNode* node, int dest, string& path) -> void {
            if (node->val == dest) {lca2dest = path; return;}
            if (node->left)  {
                path.push_back('L'); dfs(node->left, dest, path); path.pop_back();
            }
            if (node->right)  {
                path.push_back('R'); dfs(node->right, dest, path); path.pop_back();
            }
        };
        string path = "";
        auto lca_node = lca(root);
        if (lca_node->val != startValue && lca_node->val != destValue) {
            dfs(lca_node, destValue, path); auto right = lca2dest;
            // start -> lca 转换为对应数量的 U，这里不够优雅
            path = ""; dfs(lca_node, startValue, path); string left(lca2dest.length(), 'U');    
            return left + right;
        }
        if (lca_node->val == startValue){ dfs(lca_node, destValue, path); return lca2dest;}
        if (lca_node->val == destValue) {dfs(lca_node, startValue, path); return string(lca2dest.length(), 'U');}
        return "";
    }
};