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

// 同 919
class CBTInserter {
private:
    vector<TreeNode*> tree;
public:
    CBTInserter(TreeNode* root) {
        vector<TreeNode*> cur; cur.push_back(root);
        while (!cur.empty()) {
            vector<TreeNode*> nxt;
            for (auto& node:cur) {
                tree.push_back(node);
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            cur = move(nxt);
        }

    }
    
    int insert(int val) {
        int fa = (tree.size()-1)/2;
        cout << fa << endl;
        tree.push_back(new TreeNode(val));
        if (!tree[fa]->left) tree[fa]->left = tree.back();
        else tree[fa]->right = tree.back();
        return tree[fa]->val;
    }
    
    TreeNode* get_root() {
        return tree[0];
    }
};
