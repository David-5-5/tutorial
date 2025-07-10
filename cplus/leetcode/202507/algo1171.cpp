#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.10 综合应用
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
    ListNode* removeZeroSumSublists(ListNode* head) {
        // 参考题解 - 这个链表的技巧太高级了 - 只会用数组完成
        ListNode dummy(0, head);
        unordered_map<int, ListNode*> seen;
        int prefix = 0;
        for (ListNode* node=&dummy; node; node=node->next) {
            prefix += node->val;
            seen[prefix] = node;
        }
        prefix = 0; 
        for (ListNode* node=&dummy; node; node=node->next) {
            prefix += node->val;            // 手玩 体会
            node->next = seen[prefix];
        }
        return dummy.next;
    }
};