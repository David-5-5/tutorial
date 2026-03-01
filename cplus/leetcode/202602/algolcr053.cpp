#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
// LCR series
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        bool found = false; TreeNode* ans = nullptr;

        auto dfs = [&] (this auto&& dfs, TreeNode* cur) -> void {
            if (cur == nullptr) return;
            dfs(cur->left);

            if (found == true) {
                if (ans == nullptr) ans = cur;
                return;
            }else if (cur->val == p->val) (found = true);
            
            dfs(cur->right);
        };

        dfs(root);
        return ans;
    }
};