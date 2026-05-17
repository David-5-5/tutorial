#include <bits/stdc++.h>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
// LCR 同 426 会员题
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        // 递归的思路 root 和 左子树的最大节点连接， 和右子树的最小节点连接
        Node head(0, NULL, root);
        
        auto dfs = [&](this auto&& dfs, Node* node) -> pair<Node*, Node*> {
            Node* min = node, * max = node;
            if (head.right->val > node->val) head.right = node; // head->right 指向最小节点
            
            if (node->left != NULL) {
                auto lchild = dfs(node->left);
                node->left = lchild.second; lchild.second->right = node;
                min = lchild.first;
            }
            
            if (node->right != NULL) {
                auto rchild = dfs(node->right);
                node->right = rchild.first; rchild.first->left = node;
                max = rchild.second;
            }
            return {min, max};
        };
        if (root == NULL) return root;
        auto [min, max] = dfs(root);
        min->left = max; max->right = min;
        return head.right;
    }
};