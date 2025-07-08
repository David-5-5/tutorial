#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.7 双指针
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
    ListNode* oddEvenList(ListNode* head) {
        // 自行解答
        if (head == nullptr) return head;

        // head = odd_head
        auto odd = head, even = head->next, even_head = even;
        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = even->next->next;
            even = even->next;
        }
        odd->next = even_head;
        return head;
    }
};