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
    int pairSum(ListNode* head) {
        // 自行解答，快慢指针
        ListNode dummy(0, head);
        auto slow = &dummy, quick = &dummy; // 慢的走1步，快的走2步
        int ans = 0, mid = 0;
        stack<int> st;
        while (true) {
            // 偶数个节点 quick->next quick->next->next 同时存在
            // 简化条件 判断 quick->next 即可
            if (!mid && quick->next) quick = quick->next->next;
            else mid = 1;   // 找到中间节点

            slow = slow->next;
            if (slow == nullptr) break;
            if (!mid)
                st.push(slow->val);
            else {ans = max(ans, slow->val+st.top()); st.pop();}
        }
        return ans;

    }
};