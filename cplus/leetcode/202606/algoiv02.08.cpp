#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 同 142
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        set<ListNode*> seen;
        while (head != nullptr) {
            if (seen.count(head)) return head;
            seen.insert(head);
            head = head->next;
        }

        return nullptr;
    }

    ListNode *detectCycle2(ListNode *head) {
        // 复习 快慢指针
        auto fast = head, slow = head;
        while (fast != nullptr) {
            slow = slow->next;
            if (fast->next == nullptr) return nullptr;
            fast = fast->next->next;
            if (fast == slow) {
                auto ptr = head;
                while (ptr != slow) {
                    ptr = ptr->next; slow = slow ->next;
                }
                return ptr;
            }
        }

        return nullptr;  
    }    
};