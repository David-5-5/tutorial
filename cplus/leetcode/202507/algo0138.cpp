#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

// 链表 - 1.11 其他
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return head;
        Node* n_head = new Node(head->val);
        unordered_map<Node*, Node*> randoms;


        auto cur = head, n_cur = n_head;
        while (cur) {
            randoms[cur] = n_cur;
            
            cur = cur->next;
            if (cur){
                n_cur->next = new Node(cur->val);
               
            } n_cur = n_cur->next;
        }
        cur = head, n_cur = n_head;
        while (cur) {
            if (cur->random) n_cur->random = randoms[cur->random];
            cur = cur->next; n_cur = n_cur->next;
        }
        return n_head;
    }
};