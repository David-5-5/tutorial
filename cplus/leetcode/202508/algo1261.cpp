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

// 二叉树 - 2.16 其他
class FindElements {
private:
    set<int> vals;
public:
    FindElements(TreeNode* root) {
        auto dfs = [&](this auto&& dfs, TreeNode* node, int x) -> void{
            vals.insert(x);
            if (node->left) dfs(node->left, x*2+1);
            if (node->right) dfs(node->right, x*2+2);
        };
        dfs(root, 0);
    }
    
    bool find(int target) {
        return vals.count(target);
    }
};