#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.6 快慢指针
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
    ListNode* middleNode(ListNode* head) {
        // 自行解答，快慢指针
        ListNode dummy(0, head);
        auto slow = &dummy, quick = &dummy;
        while (true) {
            slow = slow->next;
            if (quick->next &&quick->next->next) quick = quick->next->next;
            else return slow;
        } 
    }
};