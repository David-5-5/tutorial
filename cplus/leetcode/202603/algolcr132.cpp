#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    int cuttingBamboo(int bamboo_len) {
        // 动态规划 O(n^2)
        vector<int> dp(bamboo_len+1);
        dp[0] = 1; dp[1] = 1; // 至少分两段
        for (int i=2; i<=bamboo_len; i++) {
            for (int len=i-1; len; --len) {
                // max(dp[i-len],(i-len)) 剩下的 i-len 可以不拆分
                // 比如 dp[3] = 2, dp[6] = 3 * 3 > 3 * dp[3]
                dp[i] = max(dp[i], max(dp[i-len],(i-len)) * len);
            }
        }
        return dp[bamboo_len];

    }
    
    int cuttingBamboo2(int bamboo_len) {
        // 贪心
        const int mod = 1e9 + 7;
        auto pow = [] (long long base, int exp, int modulo) -> int {
            base %= modulo;
            long long res = 1;
            while (exp > 0)
            {
                if (exp & 1)
                    res = res * base % modulo;
                base = base * base % modulo;
                exp >>= 1;
            }
            return res;
        };

        if (bamboo_len <= 3) return bamboo_len - 1;
        int div = bamboo_len / 3, rem = bamboo_len % 3; 
        
        if (rem == 0) return pow(3, div, mod);
        else if (rem == 1) return 4LL * pow(3, div -1, mod) % mod;
        else return 2LL * pow(3, div, mod) % mod;        
    }

};