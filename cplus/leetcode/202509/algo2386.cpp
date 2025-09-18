#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.7 搜索 
class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        // 复习 如何 不重不漏 的生成递增的子序列
        // 最大的子序列就是和为整数的元素之和
        // 求解第 k 个子序列就是从 nums 减去正的或加上负数，
        // 转换为减去所有整数构成的递增子序列，减去第 k-1 个递增子序列，即为第 k 个最大的子序列
        // 周赛 307 的视频讲解
        long long tot = 0; int n = nums.size();
        for (int i=0; i<n; ++i) {
            if (nums[i]>0) tot += nums[i];
            else nums[i] *= -1;
        }

        sort(nums.begin(), nums.end());
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.emplace(0, 0);
        while (k>1) {
            k --;
            auto [sub_sum, i] = pq.top(); pq.pop();
            if (i == n) continue;
            pq.emplace(sub_sum+nums[i], i+1);
            if (i>0) pq.emplace(sub_sum+nums[i]-nums[i-1], i+1);
        }
        return tot - pq.top().first;
    }
};