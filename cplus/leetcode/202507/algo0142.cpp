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
    ListNode *detectCycle(ListNode *head) {
        // 自行解答，不需要快慢指针
        unordered_set<ListNode*> hash;
        auto cur = head;
        while (cur) {
            if (hash.count(cur)) return cur;
            hash.insert(cur);
            cur = cur->next;
        }
        return nullptr;
    }

    ListNode *detectCycle2(ListNode *head) {
        // 参考题解，快慢指针
        // 不要哑的头节点
        auto slow = head, quick = head; // 慢的走1步，快的走2步
        while (quick != nullptr) {
            slow = slow->next;
            if (quick->next == nullptr) return nullptr;
            quick = quick->next->next;
            if (slow == quick) {
                ListNode *ptr = head;
                while (ptr != slow) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return nullptr;
    }    
};