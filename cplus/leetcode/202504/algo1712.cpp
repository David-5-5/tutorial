#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int waysToSplit(vector<int>& nums) {
        // 自行解答，勉强通过，这个边界情况，搞得头大
        const int mod = 1e9 + 7;

        int n = nums.size();

        vector<int> pres(n+1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + nums[i];

        int ans = 0;
        for (int i=1; i<n; i++) {
            int left = pres[i];
            int mid_mn = ranges::upper_bound(pres, 2*left-1) - pres.begin();
            int mid_mx = ranges::lower_bound(pres, left + (pres[n]-left)/2+1) - pres.begin();
            if (mid_mx > n || pres[mid_mx] > left + (pres[n]-left)/2) mid_mx --;

            // cout << left << "," << mid_mn << ", " << mid_mx << endl;
            ans = (ans + max(0, min(n-1,mid_mx)-max(i+1,mid_mn)+1)) % mod;
        }
        return ans;  
    }

};