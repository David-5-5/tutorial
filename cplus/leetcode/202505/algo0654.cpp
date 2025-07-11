#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 进阶

/**
 * Definition for a binary tree node.
 */
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        // 参考题解 递归 时间复杂度 O(n^2)
        auto dfs = [&] (this auto&& dfs, int left, int right) -> TreeNode* {
            if (left > right) {
                return nullptr;
            }
            // find 最大值作为根节点
            int root = left;
            for (int i=left+1; i<=right; ++i) {
                if (nums[i] > nums[root]) root = i;
            }
            TreeNode* node = new TreeNode(nums[root]);
            node->left = dfs(left, root-1);
            node->right = dfs(root+1, right);
            return node;
        };

        return dfs(0, nums.size()-1);  
    }

    TreeNode* constructMaximumBinaryTree2(vector<int>& nums) {
        // 栈 - 自行解答
        stack<TreeNode*> st;
        for (auto& v : nums) {
            TreeNode* cur = new TreeNode(v);

            TreeNode* left = nullptr;       // 这是关键
            while (st.size() && st.top()->val < v) {
                st.top()->right = left;     // 这是关键
                left = st.top();
                st.pop();
            }
            // st  栈底 node_n .. node3 node2 node1  栈顶
            //             cur
            //           /  left
            //      node3 
            //          \ right
            //         node2
            //              \   right
            //            node1
            cur->left = left;               // cur-> left 
            st.push(cur);
        }
        while (st.size() > 1) {
            TreeNode* right = st.top();
            st.pop();
            st.top()->right = right;
        }

        return st.top(); 

    }
};