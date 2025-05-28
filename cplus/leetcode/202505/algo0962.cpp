#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 扩展
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        // 参考题解 - 栈
        int n = nums.size(), ans = 0;
        stack<int> st;
        st.push(0);
        for (int i=1; i<n; ++i) 
            if (nums[st.top()] > nums[i])
                st.push(i);
        
        for (int i=n-1; i>=ans; --i) {
            while (st.size() && nums[st.top()] <= nums[i]) {
                // 倒序遍历 nums，后续的 i 变小 因此 st.top()
                // 后续的 i - st.top > i' - top()
                ans = max(ans, i-st.top());     
                st.pop();
            }
        }

        return ans;
        
    }
};