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
    ListNode* deleteMiddle(ListNode* head) {
        // 自行解答，快慢指针
        ListNode dummy(0, head);
        auto slow = &dummy, quick = &dummy; // 慢的走1步，快的走2步
        while (true) {
            if (quick->next &&quick->next->next) quick = quick->next->next;
            else {
                slow->next = slow->next->next;  // 删除中间节点
                break;
            }
            slow = slow->next;
        }
        return dummy.next;
    }
};