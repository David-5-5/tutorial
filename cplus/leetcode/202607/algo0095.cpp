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

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        // 自行解答
        vector<int> arr; vector<TreeNode*> ans; 

        for (int i=1; i<=n; i++) arr.emplace_back(i);
        // 对有序数组，遍历每个节点作为根节点，左右作为区间子树，
        // 左右的区间子树是一个规模更小的子问题
        auto dfs = [&](this auto&& dfs, int l, int r) -> vector<TreeNode*> {
            if (l > r) return {nullptr};
            if (l == r) return {new TreeNode(arr[l])};
            
            vector<TreeNode*> res;
            for (int i=l; i<=r; i++) {
                vector<TreeNode*> left = dfs(l, i-1);
                vector<TreeNode*> right = dfs(i+1, r);
                for (auto & l_tn: left) for (auto & r_tn: right) {
                    res.emplace_back(new TreeNode(arr[i], l_tn, r_tn));
                }
            }

            return res;
        };
        
        return dfs(0, n-1);    
    }
};