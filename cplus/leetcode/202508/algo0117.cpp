#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

// 二叉树 - 2.14 链表+二叉树
class Solution {
public:
    Node* connect(Node* root) {
        // 自行解答 BFS
        vector<Node*> cur; if(root) cur.push_back(root);
        while (!cur.empty()) {
            int n = cur.size(); vector<Node*> nxt;
            for (int i=0; i<n; ++i) {
                if (cur[i]->left) nxt.push_back(cur[i]->left);
                if (cur[i]->right) nxt.push_back(cur[i]->right);
                if (i+1 < n) cur[i]->next = cur[i+1];
            }
            cur = move(nxt);
        }

        return root;
    }
};