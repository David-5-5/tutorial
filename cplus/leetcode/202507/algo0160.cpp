#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.7 双指针
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // 参考题解，双指针，遍历两遍，空间复杂度O(1)
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        auto pA = headA, pB = headB;
        while (pA != pB) {
            pA = (pA == nullptr ? headB : pA->next);
            pB = (pB == nullptr ? headA : pB->next);
        }
        return pA;      
    }

    ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB) {
        // 参考题解，哈希表 容易理解 空间复杂度O(n)
        unordered_set<ListNode*> vis;
        auto ptrA = headA;
        while (ptrA) {
            vis.emplace(ptrA); ptrA = ptrA->next;
        }
        auto ptrB = headB;
        while (ptrB) {
            if (vis.count(ptrB)) return ptrB;
            ptrB = ptrB->next;
        }
        return nullptr;      
    }    
};