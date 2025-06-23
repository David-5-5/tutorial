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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // 自行解答，效率为啥这么差
        int first = -1, last = -1;
        int mn = INT_MAX, mx = 0;

        int prev = head->val, inx=0;
        ListNode* cur = head->next;

        while (cur->next !=nullptr) {
            inx ++;
            if ((cur->val > prev && cur->val > cur->next->val)||
                    (cur->val < prev && cur->val < cur->next->val)) {
                // 极大值
                if (last != -1) {
                    mn = min(mn, inx - last);
                    mx = max(mx, inx - first);
                }
                if (first == -1) first = inx;
                last = inx;
            }
            prev = cur->val; cur = cur->next;
        }

        if (mx == 0) return {-1,-1};
        else return {mn, mx};         
    }

    vector<int> nodesBetweenCriticalPoints2(ListNode* head) {
        // 参考题解后，修改上述代码
        int first = -1, last = -1;
        int mn = INT_MAX, mx = 0;

        int inx=0;
        ListNode* cur = head;

        while (cur->next->next) {   // 一键三连
            inx ++;
            if ((cur->next->val > cur->val && cur->next->val > cur->next->next->val)||
                   (cur->next->val < cur->val && cur->next->val < cur->next->next->val)) {
                // 极大值
                if (last != -1) {
                    mn = min(mn, inx - last);
                    mx = max(mx, inx - first);
                }
                if (first == -1) first = inx;
                last = inx;
            }
            cur = cur->next;
        }

        if (mx == 0) return {-1,-1};
        else return {mn, mx};     

    }    
};