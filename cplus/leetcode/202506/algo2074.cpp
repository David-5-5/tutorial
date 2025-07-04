#include <bits/stdc++.h>
using namespace std;

// 链表 - 1.4 反转链表
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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        // 自行解答，反转列表
        int grp = 2;
        auto prev = head, begin = head->next;

        while (begin) {
            // 达到 odd 组的最后一个节点
            int cnt = 1;
            auto end = begin;
            for (int _=0; _<grp-1&&end->next; ++_) {
                end = end->next;
                cnt ++;
            }
            auto nxt_prev = end;            // 不翻转指向end，翻转指向 begin
            if (cnt % 2 == 0) {             // 翻转 begin - end
                auto cur = begin;
                auto rev_prev = end->next; end->next = nullptr;
                // BEGIN -- 翻转链表，通用模板
                while (cur) {   // 冗余 cur 保持代码清晰
                    auto tmp = cur->next;
                    cur->next = rev_prev;
                    rev_prev = cur;
                    cur = tmp;
                }
                // END -- 翻转链表，通用模板
                prev->next = end, nxt_prev=begin;
            }
            grp ++, prev = nxt_prev, begin = prev->next;
        }

        return head;
    }
};