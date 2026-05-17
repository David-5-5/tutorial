#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // 复习 方案一 堆
        priority_queue<pair<int, int>> pq;    // 大根堆
        int n = nums.size(); 
        vector<int> ans;
        for (int i=0; i<k-1; i++) pq.emplace(nums[i], i);

        for (int i=k-1; i<n; i++) {
            pq.emplace(nums[i], i);
            while (pq.top().second + k <= i) pq.pop();
            ans.emplace_back(pq.top().first);
        }
        return ans;    
    }

    vector<int> maxSlidingWindow2(vector<int>& nums, int k) {
        // 复习 方案二 滑动窗口 
        deque<int> que;    // 单调递减队列
        int n = nums.size();  vector<int> ans;

        for (int i=0; i<n; i++) {
            while (!que.empty() && nums[que.back()]<nums[i]) que.pop_back();
            que.emplace_back(i);
            while (que.front() + k <= i) que.pop_front();
            if (i>=k-1) ans.push_back(nums[que.front()]);
        }
        return ans;      
    }    
};