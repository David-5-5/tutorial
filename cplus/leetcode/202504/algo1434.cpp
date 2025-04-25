#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        // 自行解答，超时
        const int mod = 1e9 + 7;
        int n = hats.size();
        
        unordered_map<long, int> memo;
        auto dfs = [&](this auto&& dfs, long s) -> int {
            int i = __builtin_popcount(s);
            if (i == n) return 1;
            
            if (memo.count(s)) return memo[s];

            long res = 0;
            for (auto& v : hats[i]) {
                if ((s>>v & 1) == 0) {
                    res += dfs(s|(long)1<<v);
                }
            }
            return memo[s] = (res % mod);
        };

        return dfs(0);
    }


};