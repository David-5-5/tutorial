#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.4 子集状压 DP
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        // 自行解答
        unordered_map<int, int> cnt_map;
        for (auto& v : nums) cnt_map[v] ++;
        vector<int> cnt;
        for (auto& [_, v]: cnt_map) cnt.push_back(v);        

        int  n = cnt_map.size(), m = 1 << quantity.size();
        
        vector<int> comb(m);
        for (int i=0; i<quantity.size(); ++i) {
            int low = 1 << i;
            for (int j=0; j<low; ++j) 
                comb[j|1<<i] = comb[j] + quantity[i];
        }

        vector<vector<int>> dp(n+1, vector<int>(m, false));
        for (int i=0; i<=n; i++) dp[i][0] = true;

        for (int i=0; i<n; ++i) for (int mask=0; mask<m; ++mask) {
            if (dp[i][mask]==false) continue;
            dp[i+1][mask] = true;  // 关键一步
            int exclusive = m - 1 - mask;   // mask 补集的子集遍历
            int sub = exclusive;
            while (sub) {
                if (cnt[i] >= comb[sub]) dp[i+1][mask|sub] = true;
                sub = (sub-1) & exclusive;  // 子集遍历
            }
        }

        return dp[n][m-1];

    }
};