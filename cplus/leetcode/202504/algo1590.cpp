#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.2 前缀和与哈希表
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        vector<long> pres(n+1);

        for (int i=0; i<n; i++) pres[i+1] = pres[i] + nums[i];

        int rem = pres[n] % p, ans = n;
        if (rem == 0) return 0;
        
        unordered_map<int, int> left;
        for (int i=0; i<=n; i++) {
            int x = pres[i] % p;
            int l = (p + x - rem) % p;
            if (left.count(l)) {
                ans = min(ans, i - left[l]);
            }
            left[x] = i;
        }
        return ans == n ? -1 :ans;   
    }
};