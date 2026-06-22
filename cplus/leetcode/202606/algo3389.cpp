#include <bits/stdc++.h>
using namespace std;

// 七、其他线性 DP - 7.1 一维 DP
class Solution {
public:
    int makeStringGood(string s) {
        vector<int> cnt(26);
        for (auto ch: s) {
            cnt[ch-'a'] ++;
        }

        int mx = ranges::max(cnt), ans = INT_MAX;
        for (int t=0; t<=mx; t++) {
            vector<int> dp(27);
            dp[25] = min(cnt[25], abs(t-cnt[25]));
            for (int i=24; i>=0; i--) {
                auto x = cnt[i], y  = cnt[i+1];
                dp[i] = dp[i+1] + min(x, abs(t-x));
                if (y < t) {
                    if (x < t) dp[i] = min(dp[i], dp[i+2] + max(x, t-y));
                    else dp[i] = min(dp[i], dp[i+2] + max(x-t, t-y));
                }
            }
            ans = min(ans, dp[0]);
        }

        return ans;
    }
};