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
    ListNode* partition(ListNode* head, int x) {
        ListNode dummy(0, head);
        ListNode *tail = & dummy;

        // initial pointers of tail, prev, cur 
        // tail is pointer of end of small value
        // prev is previous of cur
        // cur is travese of list
        while (tail->next!=nullptr && tail->next->val < x) {
            tail = tail->next;
        }
        auto prev = tail, cur = tail->next;

        while (cur != nullptr) {
            if (cur->val >= x) {
                prev = cur; cur = cur->next;
            } else {
                auto less = cur;
                prev->next = cur->next; cur = prev->next;

                less->next = tail->next; tail->next = less;
                tail = less;
            }
        }
        return dummy.next;
    }
};