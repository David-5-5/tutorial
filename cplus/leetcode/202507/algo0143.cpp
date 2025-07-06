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
    void reorderList(ListNode* head) {
        // 自行解答，快慢指针
        ListNode dummy(0, head);
        auto slow = &dummy, quick = &dummy; // 慢的走1步，快的走2步
        ListNode *tail = &dummy;
        while (true) {
            tail = slow; slow = slow->next;
            if (quick->next &&quick->next->next) quick = quick->next->next;
            else break;
        }
        tail->next = nullptr; // head 为前半段，slow 为后半段的头节点

        // 函数实现 翻转链表
        auto reverse = [](ListNode *head) -> ListNode * {
            ListNode * pre = nullptr, *cur = head;
            while (cur) {
                auto nxt = cur->next;
                cur->next = pre;
                pre = cur;
                cur = nxt;
            }
            return pre;
        };
        slow = reverse(slow);
        // 函数实现 合并链表
        auto merge = [](ListNode *node1, ListNode *node2) -> ListNode* {
            ListNode dummy(0);
            auto tail = &dummy, cur1= node1, cur2= node2;
            while (cur1 && cur2) {
                tail->next = cur1; cur1 = cur1->next;
                tail->next->next = cur2; cur2 = cur2->next;
                tail = tail->next->next; tail->next = nullptr;
            }
            if (cur1) tail->next = cur1;
            if (cur2) tail->next = cur2;

            return dummy.next;
        };

        head = merge(dummy.next, slow); 
    }
};