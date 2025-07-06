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
    bool isPalindrome(ListNode* head) {
        // 快慢指针再翻转列表的方法实在不直观
        // 还是把值复制到数组，然后双指针的做法特别直观
        // 分别调用 876的中间列表，以及 026 的反转列表解答本题
        auto cur = head;
        vector<int> arr;
        while (cur) {
            arr.push_back(cur->val); cur = cur->next;
        }
        int l = 0, r = arr.size()-1;
        while (l < r) {
            if (arr[l++] != arr[r--]) return false;
        }
        return true;
    }
};