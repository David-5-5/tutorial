#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.2 删除节点
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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* list2_end = list2;
        ListNode* cur = list1;
        while (list2_end->next) list2_end = list2_end->next;

        int inx = 0;
        while (inx < b) {
            inx ++;
            ListNode* prev = cur;
            cur = cur->next;
            if (inx == a) {
                prev->next = list2;
            }
            if (inx == b) {
                list2_end->next = cur->next;
                cur->next = nullptr;
            }

        }
        return list1;
    }
};