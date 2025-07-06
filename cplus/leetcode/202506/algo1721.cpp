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
    ListNode* swapNodes(ListNode* head, int k) {
        int n = 1;
        auto cur = head;
        while (cur->next) {n ++; cur = cur->next;}
        ListNode* kth, *revkth;
        cur = head;
        for (int i=0; i<max(k, n-k+1); ++i) {
            if (i == k-1) kth = cur;
            if (i == n-k) revkth = cur;
            cur = cur->next;
        }
        swap(kth->val, revkth->val);
        return head;
    }
};