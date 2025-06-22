#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 专题：跳跃游戏
class Solution {
public:
    int busRapidTransit(int target, int inc, int dec, vector<int>& jump, vector<int>& cost) {
        // 参考题解 逆向递归
        const int mod = 1e9 + 7;
        int n = jump.size();

        unordered_map<int, long> memo;
        auto dfs = [&] (this auto&& dfs, int pos) -> long {
            if (pos == 0) return 0;
            if (pos == 1) return inc;

            if (memo.count(pos)) return memo[pos];
            long res = (long) pos * inc;    // 全部步行的时间
            for (int i=0; i<n; ++i) {
                // 计算商 及 余数，商为公交的上一站，余数为步行的站数
                // pos = 13 jump = 5，得到 prev = 2，rem = 3  
                // 走法一 2*5 + 3 = 13
                // 走法二 3*5 - 2 = 15
                int prev = pos / jump[i], rem = pos % jump[i];  
                res = min(res, dfs(prev) + cost[i] + (long)rem * inc);
                if (rem) res = min(res, dfs(prev+1) + cost[i] + (long)(jump[i]-rem)*dec);
            }
            return memo[pos] = res;
        };

        return dfs(target) % mod;

    }
};