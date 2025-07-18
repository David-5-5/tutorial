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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        
        auto dfs = [&] (this auto&& dfs, TreeNode* u, TreeNode* v) -> bool {
            // 两个变量，四种情况，简单清晰
            if (u == nullptr && v == nullptr) return true;
            if (u == nullptr && v != nullptr) return false;
            if (u != nullptr && v == nullptr) return false;
            
            if (u->val != v->val) return false;

            return dfs(u->left, v->left) && dfs(u->right, v->right);

        };

        return dfs(p, q); 
        
    }
};