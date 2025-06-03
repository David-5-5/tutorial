#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 基础
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // 暴力写法 O(n^2), 单调栈 O(n)
        // 参考题解
        unordered_map<int, int> ids;
        int n = nums1.size(), m = nums2.size();
        for (int i=0; i<n; ++i) ids[nums1[i]] = i;

        vector<int> ans(n, -1);
        stack<int> st;      // 单调栈递减
        for (int i=0; i<m; ++i) {
            while (st.size() && st.top() < nums2[i]) {
                if (ids.count(st.top())) ans[ids[st.top()]] = nums2[i];
                st.pop();
            }
            st.push(nums2[i]);
        }

        return ans;
    }
};