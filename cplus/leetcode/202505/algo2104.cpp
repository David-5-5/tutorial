#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 贡献法
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        // 贡献法，自行解答
        long long mxs = 0, mns = 0;
        int n = nums.size();
        vector<int> suf(n, n);
        stack<pair<int, int>> st;
        
        // Calcuate maximum for suffix
        st.push({INT_MAX, n});
        for (int i=n-1; i>=0; --i) {
            while (st.top().first < nums[i]) st.pop();
            suf[i] = st.top().second;
            st.push({nums[i], i});
        }
        while (!st.empty()) st.pop();
        st.push({INT_MAX, -1});
        for (int i=0; i<n; ++i)  {      
            // 相等的情况下，右边覆盖更多的范围
            while (st.top().first <= nums[i]) st.pop();
            mxs += (long) nums[i] * (i-st.top().second) * (suf[i]-i);
            st.push({nums[i], i});
        }

        // Calcuate mininums for suffix
        while (!st.empty()) st.pop();
        st.push({INT_MIN, n});
        for (int i=n-1; i>=0; --i) {
            while (st.top().first > nums[i]) st.pop();
            suf[i] = st.top().second;
            st.push({nums[i], i});
        }
        while (!st.empty()) st.pop();
        st.push({INT_MIN, -1});
        for (int i=0; i<n; ++i)  {
            // 相等的情况下，右边覆盖更多的范围
            while (st.top().first >= nums[i]) st.pop();
            mns += (long) nums[i] * (i-st.top().second) * (suf[i]-i);
            st.push({nums[i], i});
        }

        return mxs - mns;
    }
};