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

    int maxWidthRamp2(vector<int>& nums) {
        // 递减队列，二分查找
        vector<pair<int, int>> dec;

        auto binary_search_le = [&](int target) {
            int left = 0, right = dec.size() - 1;
            int result = -1;  // 初始化为未找到
            
            while (left <= right) {
                int mid = left + (right - left) / 2;
                
                if (dec[mid].first <= target) {
                    result = mid;        // 记录当前可能的答案
                    right = mid - 1;     // 继续向左查找更小的索引
                } else {
                    left = mid + 1;      // 向右查找
                }
            }
            
            return result;
        };
        dec.push_back({nums[0], 0});
        
        int ans = 0;
        for (int i=1; i<nums.size(); ++i) {
            int j = binary_search_le(nums[i]);
            if (j != -1)  ans = max(ans, i- dec[j].second);
            if (nums[i] < dec.back().first)  dec.push_back({nums[i], i});
        }

        return ans;

    }
};