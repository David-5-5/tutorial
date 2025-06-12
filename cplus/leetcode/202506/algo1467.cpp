#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 15. 概率/期望 DP
class Solution {
public:
    double getProbability(vector<int>& balls) {
        int n = balls.size();
        vector<int> pres(n+1);        
        for (int i=0; i<n; ++i) pres[i+1] = pres[i] + balls[i];

        auto comb = [] (int n, int k) -> long{
            long res = 1;
            for (int i=1; i<=n; ++i) res *= i;
            for (int i=1; i<=k; ++i) res /= i;
            for (int i=1; i<=n-k; ++i) res /= i;
            return res;
        };
        
        auto dfs = [&](this auto&& dfs, int i, int s, int c) -> long {
            if (i == n) return c == 0;
            
            long res = 0;
            int begin = max(0, pres[i+1] - s - pres[n]/2), end = min(pres[n]/2-s, balls[i]);
            for (int j=begin; j<=end; ++j) {
                res += dfs(i+1, s+j, c+(j>0)-(j<balls[i])) * comb(balls[i], j);
            }
            return res;
        };
        double ans = 1.0 * dfs(0, 0, 0);
        // 由于计算比例，避免计算combine时溢出，将组合数单独计算
        // ans / combine(2*n,n) -> ans *= n / 2n, ans*=(n-1)/(2n-1), ... ans*=1.0/(n+1)
        for (int i=pres[n]; i>pres[n]/2; --i)
            ans *= 1.0 * (i-pres[n]/2)/i;
        return ans;     
    }
};