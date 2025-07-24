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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        //  自行解答，思维最重要，相比 aglo 100，仅增加一条语句
        auto dfs = [&] (this auto&& dfs, TreeNode* u, TreeNode* v) -> bool {
            // 两个变量，四种情况，简单清晰
            if (u == nullptr && v == nullptr) return true;
            if (u == nullptr && v != nullptr) return false;
            if (u != nullptr && v == nullptr) return false;
            
            if (u->val != v->val) return false;

            return (dfs(u->left, v->left) && dfs(u->right, v->right)) 
                 || (dfs(u->left, v->right) && dfs(u->right, v->left)); // 和 algo100 不同点

        };

        return dfs(root1, root2);     
    }
};