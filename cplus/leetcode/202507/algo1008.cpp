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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        // 自行解答
        auto dfs = [&] (this auto&& dfs, int l, int r) -> TreeNode* {
            if (l > r) return nullptr;

            int right = l+1;
            while (right <= r && preorder[l]>preorder[right]) right++;    // 优化 二分
            return new TreeNode(preorder[l], dfs(l+1, right-1), dfs(right, r));
        };
        return dfs(0, preorder.size()-1);
    }
};