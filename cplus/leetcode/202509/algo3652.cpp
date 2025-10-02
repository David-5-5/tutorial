#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        // 自行解答，滑动窗口 + 前缀和
        int n = prices.size();
        vector<long long> pres_p(n+1), pres_t(n+1);
        for (int i=0; i<n; ++i) {
            pres_p[i+1] = prices[i] + pres_p[i];
            pres_t[i+1] = prices[i] * strategy[i] + pres_t[i];
        }
        long long ans = pres_t[n], diff = 0;
        for (int i=0; i+k-1<n; ++i) {
            diff = (pres_p[i+k] - pres_p[i+k/2]) - (pres_t[i+k] - pres_t[i]);
            ans = max(ans, pres_t[n] + diff);
        }
        return ans;
    
    }
};