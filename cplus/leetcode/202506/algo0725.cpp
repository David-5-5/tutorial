#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.1 遍历链表
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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int cnt = 0;
        ListNode* cur = head;
        while (cur) {
            cnt += 1; 
            cur = cur->next;
        }
        int quo = cnt / k, rem = cnt % k;
        vector<ListNode*> ans(k);
        cur = head;
        for (int i=0; i<k; ++i) {
            ans[i] = cur;
            int val = quo + (rem?1:0); if(rem) rem --;
            ListNode* prev = cur;
            
            while (val) {
                prev = cur;
                cur = cur->next;
                val --;
            }
            if (prev) prev->next = nullptr;
        }
        return ans;
    }
};