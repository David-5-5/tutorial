#include <bits/stdc++.h>
using namespace std;


// 贪心专题 - 排序不等式
class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        // 自行解答
        const int MOD = 1e9 + 7;

        int n = nums.size();
        sort(nums.begin(), nums.end());

        int count[n];
        memset(count, 0, sizeof(count));

        // 先差分
        for (auto req : requests) {
            count[req[0]] += 1;
            if (req[1]+1 < n) count[req[1]+1] -= 1;
        }

        // 求前缀和
        for (int i=1;i<n;i++) {
            count[i] += count[i-1];
        }
        sort(count, count+n);

        long ans = 0;
        for (int i=0; i<n; i++) {
            ans = (ans + (long)nums[i] * count[i]) % MOD;
        }

        return ans;
    }
};