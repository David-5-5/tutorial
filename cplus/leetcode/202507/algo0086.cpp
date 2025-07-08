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
    ListNode* partition(ListNode* head, int x) {
        // 自行解答
        ListNode lower, upper;
        auto cur = head;
        auto low_tail = &lower, up_tail = &upper;
        while (cur) {
            if (cur->val < x) {
                low_tail->next = cur;
                low_tail = cur;
            }
            else {
                up_tail->next = cur;
                up_tail = cur;
            }
            cur = cur->next;
        }

        low_tail->next = upper.next;
        up_tail->next = nullptr;
        return lower.next;
    }
};