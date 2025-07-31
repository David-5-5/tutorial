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

// 二叉树 - 2.10 创建二叉树
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        // 自行解答，还需要优化
        int i = 0, n = traversal.size();

        auto dfs = [&](this auto&& dfs, int d) -> TreeNode* {
            auto j = i+1;
            while (j<n && traversal[j]!='-') j++;

            TreeNode* cur = new TreeNode(stoi(traversal.substr(i,j-i)));
            i = j;
            if (i == n) return cur;
            bool left = true;
            for (int j=1; j<d+1; j++) if (traversal[i+j]!='-') {left = false; break;}
            if (left) {
                i += d + 1;
                cur->left = dfs(d+1);
            }
            if (i == n) return cur;

            bool right = true;
            for (int j=0; j<d+1; j++) if (traversal[i+j]!='-') {right = false;break;}
            if (right) {
                i += d + 1;
                cur->right = dfs(d+1);
            }
            return cur;
        };

        return dfs(0);
    }
};