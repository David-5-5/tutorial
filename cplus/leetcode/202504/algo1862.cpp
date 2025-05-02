#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        // 参考题解 闪过一念，起初不觉得时间复杂度满足要求
        const int mod = 1e9 + 7;

        // 统计每个数字出现的次数
        int upper = *max_element(nums.begin(), nums.end());
        vector<int> cnt(upper + 1);
        for (auto& v: nums) cnt[v] ++;

        vector<int> pres(upper+1);
        for (int i=1; i<=upper; i++) pres[i] = pres[i-1] + cnt[i];

        int ans = 0;
        for (int y=1; y<=upper; ++y) {
            if (cnt[y]) {
                for (int d=1; d*y<=upper; ++d) {
                    ans = (ans + (long) d * cnt[y] * (pres[min(upper, (d+1)*y-1)] - pres[d*y-1])) % mod;
                }
            }
        }
        return ans;    

    }
};