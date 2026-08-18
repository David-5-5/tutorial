#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        unordered_map<int, ListNode*> last;

        ListNode*  dummy = new ListNode(0, head);
        
        int pres = 0;
        auto node = dummy;
        while (node != nullptr) {
            pres += node->val;
            last[pres] = node;
            node = node->next; 
        }

        pres = 0; node = dummy;
        while (node != nullptr) {
            pres += node->val;
            if (node != last[pres]) node->next = last[pres]->next;
            node = node->next;
        }

        return dummy->next;       
    }
};
