#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 基础
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> st;
        for (int i=0; i<2*n; ++i) {
            while (st.size() && nums[st.top()] < nums[i%n]) {
                ans[st.top()] = nums[i%n];
                st.pop();
            }
            if (ans[i%n] == -1) st.push(i%n);
        }

        return ans;    
    }
};