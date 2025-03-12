#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  合法子序列 DP
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> indices;
        vector<vector<int>> dp(n, vector<int>(n));
        int ans = 0;
     
        for (int i=0; i<n; i++) {
            for (int j = i - 1; j >= 0 && arr[j] * 2 > arr[i]; j--) {
                if (indices.contains(arr[i]-arr[j])){
                    int k = indices[arr[i]-arr[j]];
                    dp[j][i] = max(dp[k][j] + 1, 3);                    
                }
                ans = max(ans, dp[j][i]);
            }
            indices[arr[i]] = i;
        }
        
        return ans > 2?ans:0;
        
    }
};