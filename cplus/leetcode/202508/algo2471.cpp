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
    int minimumOperations(TreeNode* root) {
        // 自行解答
        int ans = 0;
        vector<TreeNode*> cur; cur.push_back(root);
        while (!cur.empty()) {
            vector<TreeNode*> nxt; vector<int> nums;
            
            for (auto& node:cur) {
                nums.push_back(node->val);
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            cur = move(nxt);
            
            // 模板 离散化 置换环
            int n = nums.size(), idx[n];
            iota(idx, idx+n, 0);
            sort(idx, idx + n, [&](int i, int j) {
                return nums[i] < nums[j];
            });
            ans += n;
            vector<bool> vis(n);
            for (auto& v:idx) {
                if (vis[v]) continue;
                while (!vis[v]) {
                    vis[v] = true;
                    v = idx[v];
                }
                ans --;
            }
            // 模板 离散化 置换环

        }        
        return ans;            
                        
    }
};