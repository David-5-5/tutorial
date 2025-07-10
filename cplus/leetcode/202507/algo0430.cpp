#include <bits/stdc++.h>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};


// 链表 - 1.11 其他
class Solution {
public:
    Node* flatten(Node* head) {
        // 自行解答
        auto dfs = [](this auto&& dfs, Node* node) -> Node* {
            auto cur = node, last = node; 
            while (cur) {
                auto nxt = cur->next;
                if (cur->child) {
                    cur->next = cur->child;
                    cur->child->prev = cur;
                    auto tail = dfs(cur->child);
                    tail->next = nxt;
                    if (nxt) nxt->prev = tail;
                    cur->child = nullptr;       //  关键
                    last = tail;                
                } else  last = cur;
                cur = nxt;
            }
            return last;   // child (是否为空)不同，last 不同
        };
        dfs(head);

        return head;
    }
};

