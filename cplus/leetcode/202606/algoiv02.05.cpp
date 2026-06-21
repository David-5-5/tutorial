#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode dummy = ListNode();
        auto cur = &dummy;
        while (l1 != nullptr || l2 != nullptr) {
            auto val = (l1 != nullptr?l1->val:0) + (l2 != nullptr?l2->val:0);

            cur->next = new ListNode((val + carry) % 10);
            carry = (val + carry) / 10;
            cur = cur->next;
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }

        if (carry) cur->next = new ListNode(carry);

        return dummy.next;
    }
};