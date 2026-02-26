#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.9 分治
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
    ListNode* sortList(ListNode* head) {
        // 最简单方法
        vector<int> arr;
        auto cur = head;
        while (cur) {
            arr.push_back(cur->val); cur = cur->next;
        }
        sort(arr.begin(), arr.end());
        cur = head;
        for (auto v: arr) {cur->val = v; cur= cur->next;}
        return head;
    }
};