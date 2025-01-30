#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 爬楼梯
class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        int mod = 1e9 + 7;
        vector<int> f(high+1);
        f[0] = 1;
        
        for (int i=1; i<=high; i++) {
            if (i>=zero) f[i] = (f[i] + f[i-zero]) % mod;
            if (i>=one) f[i] = (f[i] + f[i-one]) % mod;
        }

        int ans = 0;
        for (int i=low; i<=high; i++) {
            ans = (ans + f[i]) % mod;
        }
        return ans;
    }
};