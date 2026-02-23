#include <bits/stdc++.h>
using namespace std;


/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// 同 142
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> hash;
        auto cur = head;
        while (cur) {
            if (hash.count(cur)) return cur;
            hash.insert(cur);
            cur = cur->next;
        }
        return nullptr;
    }
};