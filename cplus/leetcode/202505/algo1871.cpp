#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.1 前缀和优化 DP
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        vector<int> dp(n);
        vector<int> pres(n+1, 1);
        dp[0] = 1, pres[0] = 0;
        for (int j=minJump; j<n; ++j) {
            if (s[j] == '0' && pres[j-minJump+1]-pres[max(0, j-maxJump)]){
                dp[j] = 1;
            }
            pres[j+1] = (pres[j] + dp[j]);
        }

        return dp[n-1];    
    }
};