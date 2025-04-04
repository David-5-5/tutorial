#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.2 前缀和与哈希表
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        // 自行解答
        int n = nums.size();
        vector<int> pres(n+1);

        for (int i=0; i<n; i++) pres[i+1] = pres[i] + nums[i];

        int cnt[k], ans = 0;
        memset(cnt, 0, sizeof(cnt));
        
        for (auto& v: pres) {
            int x = v % k;
            if (x < 0) x += k;
            
            ans += cnt[x];
            cnt[x] ++;
        }
        return ans; 
    }
};