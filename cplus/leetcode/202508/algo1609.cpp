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

// 二叉树 - 2.13 二叉树 BFS
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        // 自行解答
        int even = 1;
        vector<TreeNode*> cur; cur.push_back(root);
        while (!cur.empty()) {
            int prev = even?0:1e6+1;
            vector<TreeNode*> nxt;
            for (auto& node:cur) {
                if (even) {
                    if (node->val%2 && node->val > prev) {
                        prev = node->val;
                    }else return false;
                } else {
                    if (node->val%2==0 && node->val < prev) {
                        prev = node->val;
                    } else return false;
                }
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            even ^= 1; cur = move(nxt);
        }        
        return true;
    }
};