#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        // 自行解答
        const int mod = 1e9 + 7;
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(6, vector<int>(16, -1)));
        auto dfs = [&](this auto&& dfs, int i, int p, int c) {
            if (i == n) return  1;      

            auto& res = memo[i][p][c];
            if (res != -1) return res;
            
            res = 0;
            for (int j = 0; j<6; j++) {
                if (j == p && c == rollMax[j]) continue;        // 重复的最大次数
                res = ((long)res + dfs(i+1, j, j==p?c+1:1))%mod;
            }
            return res;        
        };

        return dfs(0, 0, 0);    // 初始条件
    }
};