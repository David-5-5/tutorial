#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 合法子序列 DP
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int n = arr.size();
        unordered_map<int, int> pos;
        vector<int> dp(n, 1);
        int ans = 1;

        for (int i = 0; i<n; i++) {
            int prev = arr[i] - difference;
            if (pos.contains(prev)) {
                dp[i] = dp[pos[prev]] + 1;
            }
            pos[arr[i]] = i;
            ans = max(ans, dp[i]);
        }

        return ans;
    }
};