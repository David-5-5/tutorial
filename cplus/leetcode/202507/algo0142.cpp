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
        ListNode dummy(0, head);
        unordered_set<ListNode*> hash;
        auto cur = head;
        while (cur) {
            if (hash.count(cur)) return cur;
            hash.insert(cur);
            cur = cur->next;
        }
        return nullptr;
    }


};