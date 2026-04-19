#include <bits/stdc++.h>
using namespace std;

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
// LCR series 同 21
class Solution {
public: 
    ListNode* trainningPlan(ListNode* l1, ListNode* l2) {
        // 复兴，增加哨兵节点，比原有 22 实现更优雅
        ListNode preHead(0, l1); ListNode* pre = &preHead;

        while (l1 != nullptr && l2 != nullptr) {
            if (l2->val < l1->val) {
                pre->next = l2; l2 = l2->next; pre->next->next = l1; l1 = pre->next;
            }else {
                pre = l1; l1 = pre->next;   // next
            }
        }
        if (l2 != nullptr) pre->next = l2;

        return preHead.next;
    }
};