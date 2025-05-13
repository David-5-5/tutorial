#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.3 单调队列优化 DP
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        // 自行解答
        deque<pair<int, int>> que; // 递减的队列, 队首为最大值
        int n = nums.size(), ans = INT_MIN;
        for (int i=0; i<n; ++i) {
            while (que.size() && que.front().first+k<i) {
                que.pop_front();
            }
            
            int cur = (que.size()?que.front().second:0) + nums[i];
            while (que.size() && que.back().second < cur) {
                que.pop_back();
            }
            que.push_back({i, cur});
        }

        return que.back().second;
    }
};