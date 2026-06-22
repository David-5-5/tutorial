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

 
};