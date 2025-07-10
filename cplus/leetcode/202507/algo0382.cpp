#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 链表 - 1.11 其他
class Solution {
private:
    vector<int> arr;

public:
    Solution(ListNode* head) {
        while (head) {
            arr.emplace_back(head->val);
            head = head->next;
        }
    }
    
    int getRandom() {
        return arr[rand() % arr.size()];
    }
};
