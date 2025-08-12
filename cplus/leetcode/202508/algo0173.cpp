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
class BSTIterator {
private:
    deque<int> que;
public:
    BSTIterator(TreeNode* root) {
        auto dfs = [&](this auto dfs, TreeNode* node) -> void{
            if (!node) return;
            dfs(node->left);
            que.push_back(node->val);
            dfs(node->right);
        };
        dfs(root);
    }
    
    int next() {
        int val = que.front(); que.pop_front();
        return val;
    }
    
    bool hasNext() {
        return !que.empty();
    }
};

