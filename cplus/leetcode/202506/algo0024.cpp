#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.4 反转链表
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
    ListNode* swapPairs(ListNode* head) {
        // 自行解答
        ListNode dummy(0, head);
        ListNode* cur = & dummy;
        while (cur->next && cur->next->next) {
            auto nxt = cur->next;
            cur->next = nxt->next;
            nxt->next = cur->next->next;
            cur->next->next = nxt;

            cur = nxt;
        }

        return dummy.next;        
    }
};