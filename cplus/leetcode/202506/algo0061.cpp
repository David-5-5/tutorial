#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.5 前后指针
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
    ListNode* rotateRight(ListNode* head, int k) {
        // 自行解答 - 链表
        if (head == nullptr) return head;
        ListNode dummy(0, head);
        int cnt = 0;
        ListNode* tail = &dummy;
        while (tail->next) {
            cnt ++; tail = tail->next;
        }
        int left = cnt - (k % cnt);     // 前 left 个节点， left+1 为新的 head
        if (left != cnt) {              // left == cnt 循环一圈恢复原始链表
            ListNode* new_t = &dummy;
            for (int _=0; _<left; ++_) new_t = new_t->next; // 第 left 个节点
            tail->next = head;          // 原头节点接尾部
            dummy.next = new_t->next;   // 新的头节点
            new_t->next = nullptr;      // 新的尾节点
        }
        return dummy.next; 
    }
};