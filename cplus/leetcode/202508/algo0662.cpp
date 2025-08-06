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
    int widthOfBinaryTree(TreeNode* root) {
        // 自行解答 - 内存溢出
        int mx_widht = 1;
        deque<TreeNode*> cur; cur.push_back(root);
        while (!cur.empty()) {
            mx_widht = max(mx_widht, (int)cur.size());
            deque<TreeNode*> nxt;
            for (auto& node:cur) {
                if (node) {
                    nxt.push_back(node->left); nxt.push_back(node->right);
                }else {
                    nxt.push_back(nullptr); nxt.push_back(nullptr);
                }
            }
            while (!nxt.empty() && !nxt.front()) nxt.pop_front();
            while (!nxt.empty() && !nxt.back()) nxt.pop_back();
            cur = move(nxt);
        }

        return mx_widht;
    }

    int widthOfBinaryTree2(TreeNode* root) {
        // 自行解答
        unsigned long long mx_widht = 1;
        vector<unsigned long long> inx; inx.push_back(0);
        vector<TreeNode*>cur; cur.push_back(root);
        while (!cur.empty()) {
            if (inx.size()>1) mx_widht = max(mx_widht, inx.back()-inx[0]+1);
            vector<TreeNode*> nxt; vector<unsigned long long> n_inx;
            int n = cur.size();
            for (int i=0; i<n; ++i) {
                if (cur[i]->left) {
                    nxt.push_back(cur[i]->left); n_inx.push_back(inx[i]*2+1);
                }
                if (cur[i]->right) {
                    nxt.push_back(cur[i]->right); n_inx.push_back(inx[i]*2+2);
                }                    
            }
            cur = move(nxt); inx = move(n_inx);
        }

        return mx_widht;
    }

};