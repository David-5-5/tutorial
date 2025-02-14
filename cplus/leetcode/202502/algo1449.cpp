#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  完全背包
class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        // 思路参见 python 题解
        vector<int> dp(target+1, INT_MIN);
        dp[0] = 0;
        for (auto& c: cost) 
            for (int k=c; k<=target; k++)
                dp[k] = max(dp[k], dp[k-c] + 1);
        
        cout << dp[target] << endl;
        if (dp[target] < 0) return "0";

        string ans = "";
        int p = target;
        for (int i=9; i>0; i--) {
            while (p>=cost[i-1] && dp[p] == dp[p-cost[i-1]] + 1) {
                p -= cost[i-1];
                ans += to_string(i);
            }
        }
        return ans;    

    }
};