#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.5 其他树形 DP

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxValue(TreeNode* root, int k) {
        // 参考题解，动态规划
        // f[node][t] 表示 node 连着 t 个被染色的节点的最大值
        // node 被染色，则 f[node][t] = max(f[node_l][i] + f[node_r][j] + val_node) i + j + 1 = t
        // node 未被染色， f[node][0] = max(f[node_l][i] + f[node_l][j]) 0=<i,j<=k
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> vector<int>{
            if (node == nullptr) return vector<int>(k+1);
            
            vector<int> l = dfs(node->left);
            vector<int> r = dfs(node->right);

            vector<int> res(k+1);
            res[0] = ranges::max(l) + ranges::max(r);
            for (int i=0; i<k; ++i) for (int j=0; i+j<k; ++j) {
                res[i+j+1] = max(res[i+j+1], l[i] + r[j] + node->val);
            }
            return res;
        };

        return ranges::max(dfs(root));
    }
};