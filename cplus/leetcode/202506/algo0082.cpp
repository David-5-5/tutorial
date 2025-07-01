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
    ListNode* deleteDuplicates(ListNode* head) {
        // 自行解答
        ListNode dummy(0, head);
        // prev 指向一个队列中唯一元素
        ListNode* prev = &dummy;
        // cur 和 prev 值不同的第一个元素
        ListNode* cur  = prev->next;    
        while (cur) {
            // cur 为唯一元素，加入队列
            if (!cur->next || cur->val != cur->next->val) {
                prev = cur; cur = cur-> next;
            } else {
                // cur 用重复元素，跳过所有值和 cur->val 相同的节点
                while (cur->next && cur->val == cur->next->val) {
                    cur = cur->next;
                }
                // 找个一个新值的起始元素
                prev->next = cur->next;
                cur = prev->next;
            }
        }
        
        return dummy.next;
    }
};