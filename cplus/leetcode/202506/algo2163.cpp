#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 14. 博弈 DP
class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        // 自行解答 - 前后缀分解
        int n = nums.size() / 3;
        
        vector<long> mx_sum_suf(n+1);
        priority_queue<int, vector<int>, greater<>> suf_pq;
        for (int i=2*n; i<3*n; i++) {
            mx_sum_suf[n] += nums[i];
            suf_pq.push(nums[i]);
        }
        for (int i=2*n-1; i>=n; --i) {
            mx_sum_suf[i-n] = mx_sum_suf[i-n+1];
            if (suf_pq.top() < nums[i]) {
                mx_sum_suf[i-n] += nums[i] - suf_pq.top();
                suf_pq.pop();
                suf_pq.push(nums[i]);
            }
        }

        long pre_sum = 0;
        priority_queue<int, vector<int>, less<>> pre_pq;
        for (int i=0; i<n; ++i) {
            pre_sum += nums[i];
            pre_pq.push(nums[i]);
        }

        long ans = pre_sum - mx_sum_suf[0];
        for (int i=n; i<2*n; ++i) {
            if (pre_pq.top() > nums[i]) {
                pre_sum += nums[i] - pre_pq.top();
                pre_pq.pop();
                pre_pq.push(nums[i]);
            }
            ans = min(ans, pre_sum - mx_sum_suf[i-n+1]);
        }

        return ans;
    }
};