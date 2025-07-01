#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.2 删除节点
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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        // 自行解答
        ListNode dummy(0, head);    // 哨兵
        ListNode* cur = &dummy;
        unordered_set<int> hash(nums.begin(), nums.end());

        while (cur) {
            if (cur->next && hash.count(cur->next->val))
                cur->next = cur->next->next;
            else cur= cur->next;
        }
        return dummy.next;
    }
};