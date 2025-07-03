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
    ListNode* insertionSortList(ListNode* head) {
        // 自行解答 
        ListNode dummy(0, head);            // 哨兵
        auto prev = head, cur = head->next;
        while (cur) {
            auto tr = &dummy;
            while (tr->next->val < cur->val) {
                tr = tr->next;
            }
            if (tr == prev) {
                prev = cur;
                cur = prev->next;
            } else {
                prev->next = cur->next;
                cur->next = tr->next;
                tr->next = cur;
                cur = prev->next;
            }
        }

        return dummy.next;   
    }
};