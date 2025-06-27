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
    int numComponents(ListNode* head, vector<int>& nums) {
        set<int> exist(nums.begin(), nums.end());

        int ans = 0, cnt = 0;
        ListNode* node = head;
        while(node) {
            if (!exist.count(node->val)) {
                if (cnt) {ans ++; cnt = 0;}
            } else cnt += 1;
            node = node->next;
        }
        if (cnt) ans ++;
        return ans;    
    }
};