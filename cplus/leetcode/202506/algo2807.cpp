#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.3 插入节点
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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* node = head;
        while (node->next) {
            node->next = new ListNode(gcd(node->val, node->next->val), node->next);
            node = node->next->next;
        }
        return head;
    }
};