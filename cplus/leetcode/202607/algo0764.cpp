#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        vector dp(n, vector<int>(n,n));
        unordered_set<int> banned;
        for (auto m: mines) banned.insert(m[0] * n + m[1]);

        for (int i=0; i<n; i++) {
            int count = 0;
            for (int j=0; j<n; j++) {
                count = banned.count(i*n+j) ? 0 : count+1;
                dp[i][j] = min(dp[i][j], count);
            }
            count = 0;
            for (int j=n-1; j>=0; j--) {
                count = banned.count(i*n+j) ? 0 : count+1;
                dp[i][j] = min(dp[i][j], count);
            }
        }
        int ans = 0;
        for (int j=0; j<n; j++) {
            int count = 0;
            for (int i=0; i<n; i++) {
                count = banned.count(i*n+j) ? 0 : count+1;
                dp[i][j] = min(dp[i][j], count);
            }
            count = 0;
            for (int i=n-1; i>=0; i--) {
                count = banned.count(i*n+j) ? 0 : count+1;
                dp[i][j] = min(dp[i][j], count);
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }   
};