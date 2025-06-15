#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 进阶
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        // 参考题解
        int n = nums.size();

        // g[r] = vector<int> children，表明下标 r 是 左边最近大于 children 中下标对应的元素
        // nums[r] > nums[chilren[i]] r < children[i]
        vector<vector<int>> left_grp(n);
        // j 是 i 右边最近且大于 i 的元素
        vector<int> right(n, n);  // right[i] = j，i<j, nums[i] < nums[j]
        // 使用 stack 可以求出左右最大的元素
        stack<int> st;  // 单调递减

        for (int i=0; i<n; ++i)  {
            int x = nums[i];
            while (st.size() && x >= nums[st.top()]) {
                right[st.top()] = i;
                st.pop();
            }
            if (!st.empty()) left_grp[st.top()].push_back(i);
            st.push(i);
        }

        long long ans = 0;
        // cnt 记录当前队列中的操作数，操作数需要小于等于 k
        // l 为 窗口的左指针
        int cnt = 0, l = 0; 
        deque<int> q;       // 单调递减队列
        for (int r=0; r<n; ++r) {
            int x = nums[r];
            while (q.size() && x >= nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(r);
            cnt += nums[q.front()] - x;

            while (cnt > k) {
                int out = nums[l];
                for (int i:left_grp[l]) {
                    if (i > r) break;
                    cnt -= (out-nums[i]) * (min(right[i], r+1) - i);    // 关键点，难点
                }
                l ++;
                if (!q.empty() && q.front() < l) q.pop_front();
            }
            ans += r - l + 1;
        }
        return ans;   

    }
};