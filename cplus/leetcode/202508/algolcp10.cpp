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

// 二叉树 - 2.12 树形 DP - 复习
class Solution {
public:
    double minimalExecTime(TreeNode* root) {
        // 参考题解 - 解法二
        // return pair<double, double> 分别为全部执行时间，最小执行时间（并行）
        auto dfs = [&](this auto&& dfs, TreeNode* node)->pair<double, double>{
            if (node == nullptr){
                return {0, 0};
            }

            auto [l_tot_time, l_min_time] = dfs(node->left);
            auto [r_tot_time, r_min_time] = dfs(node->right);
            return {l_tot_time + r_tot_time + node->val, 
                node->val + max((l_tot_time+r_tot_time)/2.0, max(l_min_time, r_min_time))};
        };
        return dfs(root).second;
    }

    double minimalExecTime2(TreeNode* root) {
        // 参考题解 - 解法一
        // return pair<double, double> 分别为全部执行时间，并行时间，（最小时间=全部时间-并行时间）
        auto dfs = [&](this auto&& dfs, TreeNode* node)->pair<double, double>{
            if (node == nullptr){
                return {0, 0};
            }

            auto [a, b] = dfs(node->left);
            auto [c, d] = dfs(node->right);
            int a, b, c, c;     // a >= c
            if (a < c) {
                swap(a, c); swap(b, d);
            } 

            // a-2*b 为串行时间，正好可以和 c 并行执行
            if (a-2*b<=c) return {a+c+node->val, (a+c)/2.0};
            else return {a+c+node->val, b+c};

        };
        auto ans = dfs(root);
        return ans.first - ans.second;
    }    
};

