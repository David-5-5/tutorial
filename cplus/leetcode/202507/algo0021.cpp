#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.8 合并链表
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // 自行解答
        ListNode merge, *cur1 = list1, *cur2 = list2;
        auto tail = &merge;
        while (cur1 && cur2) {
            if (cur1->val < cur2->val) {
                tail->next = cur1;
                tail = tail->next;
                cur1 = cur1->next;
            } else {
                tail->next = cur2;
                tail = tail->next;
                cur2 = cur2->next;

            }
        }
        if (cur1) tail->next = cur1;
        if (cur2) tail->next = cur2;

        return merge.next;
    }
};