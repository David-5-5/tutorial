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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 自行解答，基于 21
        // 两种特殊情况
        if (lists.size()==0) return nullptr;
        if (lists.size() == 1) return lists[0];
        auto merge = [](ListNode* list1, ListNode* list2) -> ListNode*{
            // 自行解答
            ListNode merge, *cur1 = list1, *cur2 = list2;
            auto tail = &merge;
            while (cur1 && cur2) {
                if (cur1->val < cur2->val) {
                    tail->next = cur1;
                    tail = tail->next;
                    cur1 = cur1->next;
                } else {
                    tail->next = cur2;
                    tail = tail->next;
                    cur2 = cur2->next;
                }
            }
            if (cur1) tail->next = cur1;
            if (cur2) tail->next = cur2;

            return merge.next;
        };

        ListNode * m = lists[0];
        for (int i=1; i<lists.size(); ++i) {
            m = merge(m, lists[i]);
        }
        return m;    
    }
};