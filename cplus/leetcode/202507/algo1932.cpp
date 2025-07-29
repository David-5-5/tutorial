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

// 二叉树 - 2.9 二叉搜索树
class Solution {
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        unordered_map<int, TreeNode*> mp;
        for (auto t: trees) mp[t->val] = t;
        unordered_map<int, int> degree; // 仅有唯一节点的degree = 0，从其开始进行拓扑排序
        // unordered_map<int, vector<int>> g; g[k].push_back(v->left->val);  g[k].push_back(v->left->val); 
        for (auto&[k, v]:mp) {
            if (!degree.count(k)) degree[k] = 0;
            if (v->left && mp.count(v->left->val)) 
                degree[v->left->val] ++;
            if (v->right && mp.count(v->right->val)) 
                degree[v->right->val] ++;
        }
        deque<int> q;
        for (auto& [k, v]: degree) if (v==0) q.push_back(k);
        // cout << q.size() << endl;
        if (q.size()>1) return nullptr; // 仅有唯一节点的degree = 0
        auto root = mp[q[0]];
        while (!q.empty()) {
            auto inx = q.front(); q.pop_front();
            auto fa = mp[inx];
            if (fa->left && mp.count(fa->left->val)) {
                fa->left = mp[fa->left->val]; degree[fa->left->val] --;
                if (degree[fa->left->val] == 0) q.push_back(fa->left->val);
            }
            if (fa->right && mp.count(fa->right->val)) {
                fa->right = mp[fa->right->val]; degree[fa->right->val] --;
                if (degree[fa->right->val] == 0) q.push_back(fa->right->val);
            }
        }
        for (auto& [_, v]: degree) if (v != 0) return nullptr;

        long pre = LONG_MIN; 
        auto isValidBST = [&](this auto&& isValidBST, TreeNode* root) {
            if (!root) return true;
            if (!isValidBST(root->left)) return false;
            if (root->val <= pre) return false;
            pre = root->val;
            return isValidBST(root->right);
        };

        if (isValidBST(root)) return root;
        else return nullptr;
    }
};