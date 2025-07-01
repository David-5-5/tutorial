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
    void deleteNode(ListNode* node) {
        // 自行解答
        ListNode* cur = node; ListNode* nxt = cur->next;
        
        while (nxt) {
            cur->val = nxt->val;
            if (nxt->next)
                cur = nxt; 
            else 
                cur->next = nullptr;
            nxt = cur->next;
        }

    }
};