#include <bits/stdc++.h>
using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

// 二叉树 - 2.15 N 叉树
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        // 自行解答
        vector<vector<int>> ans;
        vector<Node*> cur; if(root) cur.push_back(root);
        while (!cur.empty()) {
            vector<int> nums; vector<Node*> nxt;
            for (auto& node: cur) {
                nums.push_back(node->val);
                for (auto& ch : node->children) nxt.push_back(ch);
            }
            cur = move(nxt);
            ans.push_back(nums);
        }

        return ans;
    }
};