#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int countOfPairs(vector<int>& nums) {
        // 自行解答 
        const int mod = 1e9 + 7;
        int n = nums.size(), mx = ranges::max(nums);

        vector<vector<vector<int>>> memo(n+1, vector<vector<int>>(mx+1, vector<int>(mx+1, -1)));

        // i index of nums
        // s previous value of arr1
        // t previous value of arr2
        auto dfs = [&](this auto&& dfs, int i, int s, int t) -> int {
            if (i == n) return 1;
            
            auto& res = memo[i][s][t];
            
            if (res != -1) return res;

            res = 0;
            for (int n_s=s; n_s<=nums[i]; n_s++) {  // s 递增 n_s next s
                int n_t = nums[i] - n_s;            // t 递减 
                if (n_t <= t) res = ((long)res + dfs(i+1, n_s, n_t)) % mod;
            }
            
            return res;
        };

        // initial s = 0, t = mx
        // return dfs(0, 0, mx);
        // initial s = 0, t = mx
        dfs(0, 0, nums[0]);
    }

    
    int countOfPairs2(vector<int>& nums) {
        // 自行解答  降低一维，但时间复杂度未变，优化存储空间
        const int mod = 1e9 + 7;
        int n = nums.size(), mx = ranges::max(nums);

        vector<vector<int>> memo(n+1, vector<int>(mx+1, -1));
        // i index of nums
        // s previous value of arr1
        auto dfs = [&](this auto&& dfs, int i, int s) -> int {
            if (i == n) return 1;
            auto& res = memo[i][s];
            
            if (res != -1) return res;

            res = 0;
            int t = (i>0)?nums[i-1]-s:mx;

            for (int n_s=max(s,nums[i]-t); n_s<=nums[i]; n_s++) {  // s 递增 n_s next s
                res = ((long)res + dfs(i+1, n_s)) % mod;
            }            
            return res;
        };

        return dfs(0, 0);
    }    

    int countOfPairs3(vector<int>& nums) {
        const int mod = 1e9 + 7;
        int n = nums.size(), mx = ranges::max(nums);

        vector<vector<int>> dp(n, vector<int>(mx+1));
        for (int j=0; j<=nums[0]; j++) dp[0][j] = 1; // 初始值

        for (int i=1; i<n; i++) {
            for (int j=0; j<=nums[i]; j++) {
                int t = nums[i-1]-j;
                for (int n_s=max(j,nums[i]-t); n_s<=nums[i]; n_s++) {  // s 递增 n_s next s
                    dp[i][n_s] = (dp[i][n_s] + dp[i-1][j]) % mod;
                }            
            }
        };


        // for (auto& r:dp) {
        //     for (auto& v:r) cout << v << ", ";
        //     cout << endl;
        // }
        int ans = 0;
        for (auto v:dp[n-1]) ans = (ans + v) % mod;
        return ans;    

    }



};