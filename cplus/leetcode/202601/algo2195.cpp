#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        // 自行解答
        sort(nums.begin(), nums.end());

        long long ans = 0; int prev = 0;
        for (auto & v : nums) {
            if (v == prev) continue;
            if (k >= v - prev - 1)
                ans +=  1LL * (v + prev ) * (v - prev - 1) / 2;
            else
                ans += 1LL * (prev+1 + prev + k) * k / 2;
            k -= min(k, v - prev - 1);

            prev = v;
            if (k == 0) break;
        }
        if (k) ans += 1LL * (prev+1 + prev + k) * k / 2;
        return ans; 
    }
};