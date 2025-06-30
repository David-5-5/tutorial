#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.1 遍历链表
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeNodes(ListNode* head) {
        // 自行解答 
        ListNode* cur = head;
        ListNode* node = cur->next;
        while (node) {
            if (node->val != 0) {
                cur->val += node->val;
            } else {
                if (node->next == nullptr) {
                    cur->next = nullptr;
                } else {
                    cur->next = node;
                    cur = node;
                }
            }
            node = node->next;
        }
        return head;
                
    }

};