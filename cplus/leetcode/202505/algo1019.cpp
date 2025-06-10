#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 进阶

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
    vector<int> nextLargerNodes(ListNode* head) {
        // 自行解答
        stack<pair<int, int>> st;
        vector<int> ans;

        ListNode* node = head;
        while (node != nullptr) {
            while (st.size() && st.top().first < node->val) {
                ans[st.top().second] = node->val;
                st.pop();
            }
            st.push({node->val, ans.size()});
            ans.push_back(0);
            node = node->next;
        }

        return ans;    
    }
};