#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  合法子序列 DP
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        // 参考题解
        int n = arr.size();
        unordered_map<int, int> indices;
        vector<vector<int>> dp(n, vector<int>(n));
        int ans = 0;
     
        for (int i=0; i<n; i++) {
            // 下面的边界条件很关键 arr[j] * 2 > arr[i] 保证 k < j
            // for (int j = i - 1; j >= 0 && arr[j] * 2 > arr[i]; j--) {
            for (int j=0; j<n; j++)  {
                if (indices.contains(arr[i]-arr[j])){
                    int k = indices[arr[i]-arr[j]];
                    if (k > j) break;
                    dp[j][i] = max(dp[k][j] + 1, 3);                    
                }
                ans = max(ans, dp[j][i]);
            }
            indices[arr[i]] = i;
        }
        
        return ans > 2?ans:0;
        
    }
};