#include <bits/stdc++.h>
using namespace std;

// 七、其他线性 DP - 7.1 一维 DP
class Solution {
public:
    int minSteps(int n) {
        // 自行解答
        vector<int> dp(n+1, INT_MAX/2); dp[1] = 0;
        int i=1, cp = 0;
        for (int i=1; i<=n; i++) {
            cp = i;
            if (i+cp<=n) dp[i+cp] = min(dp[i+cp], dp[i] + 2);
            for (int j=i+2*cp; j<=n; j+=cp)
                dp[j] = dp[j-cp] + 1;
        }
        return dp[n];  
    }

};