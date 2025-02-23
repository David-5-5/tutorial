#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        // 自行解答，直接暴力 O(mn^2)
        int m = strs.size(), n = strs[0].size();

        auto eg = [&](int x, int y) -> bool {
            for (int i=0; i<m; i++) {
                if (strs[i][x] < strs[i][y]) return false;
            }   
            return true;
        };

        vector<int> dp(n, 0);
        for (int i=0; i<n; i++) {
            for (int j=0; j<i; j++) {
                if (eg(i, j)) dp[i] = max(dp[i], dp[j]);
            }
            dp[i] += 1;
        }

        return n - ranges::max(dp);
    }
};