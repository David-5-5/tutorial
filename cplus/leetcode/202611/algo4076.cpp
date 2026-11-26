#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int resilientSubarray(vector<int>& nums, int k) {
        // 自行解答 同 4075
        int n = nums.size(); if (k == 1) return n;
        nums.emplace_back(nums.back() + 1);    // 哨兵
        int prev = nums[0] % k, cnt = 1, ans = 1;
        for (int i=1; i<=n; i++) {
            if (nums[i]%k != prev) {
                int g = gcd(k, prev);
                // (k/g) 避免 int 溢出
                ans = max(ans, ((cnt-1) / (k/g)) * (k / g) + 1);
                cnt = 1, prev = nums[i]%k;
            } else cnt += 1;
        }

        return ans;
    }
};