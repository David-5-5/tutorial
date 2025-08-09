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
    long long kthLargestLevelSum(TreeNode* root, int k) {
        // 自行解答
        vector<long long> nums;

        vector<TreeNode*> cur; cur.push_back(root);
        while (!cur.empty()) {
            long long sum = 0;
            vector<TreeNode*> nxt;
            for (auto& node:cur) {
                sum += node->val;
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            cur = move(nxt); nums.push_back(sum);
        }        
        if (nums.size()<k) return -1;
        sort(nums.begin(), nums.end());
        return nums[nums.size()-k];
    }

    long long kthLargestLevelSum(TreeNode* root, int k) {
        // 自行解答 使用set 代替 vector 更慢
        set<long long> nums;

        vector<TreeNode*> cur; cur.push_back(root);
        while (!cur.empty()) {
            long long sum = 0;
            vector<TreeNode*> nxt;
            for (auto& node:cur) {
                sum += node->val;
                if (node->left) nxt.push_back(node->left);
                if (node->right) nxt.push_back(node->right);
            }
            cur = move(nxt); nums.insert(sum);
        }        
        
        if (nums.size()<k) return -1;
        auto it = nums.begin(); advance(it, -k);
        return *it;
    }
};