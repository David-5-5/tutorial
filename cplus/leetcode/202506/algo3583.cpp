#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        // 自行解答
        const int mod = 1e9 + 7;
        int n = nums.size();
        unordered_map<int, int> cnt;
        vector<int> suf(n);
        for (int i=n-1; i; --i) {
            suf[i] = cnt[nums[i]*2];
            cnt[nums[i]] ++;
        }

        int ans = 0, pre = 0;
        cnt.clear();
        for (int i=0; i<n; ++i) {
            pre = cnt[nums[i]*2];
            ans = ((long)ans + ((long)pre * suf[i])) % mod;
            cnt[nums[i]] ++;
        }
        return ans;
    }
};