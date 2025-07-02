#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.3 插入节点
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node() {}
    Node(int _val) {
        val = _val;
        next = NULL;
    }
    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};


class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if (head == nullptr) {
            head = new Node(insertVal);
            head->next = head;
            return head;
        } 
        if (head == head->next) {
            head->next = new Node(insertVal, head);
            return head;
        }
        auto curr = head, next = head->next, node = new Node(insertVal);
        while (next != head) {  // 避免无限循环
            if (insertVal >= curr->val && insertVal <= next->val) {
                // 大于等于左，小于等于右
                break;
            }
            if (curr->val > next->val) {    // curr 最大值，next 为最小值  
                if (insertVal > curr->val || insertVal < next->val) { 
                    // 大于最大值 或 小于最小值 （等于也可以）
                    break;
                }
            }
            curr = curr->next;
            next = next->next;
        }
        curr->next = node;
        node->next = next;
        return head;
    }
};