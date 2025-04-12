#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.4 子集状压 DP
class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        // 自行解答
        int n = tasks.size();

        // 是否需要增加时间段
        auto inc = [&] (int i, int used) -> bool {
            return used+tasks[i] > sessionTime;
        };
        
        // 这个状态码的定义太漂亮了
        // vector 元素包含两个内容，
        // 前16位表示当前的时间段，从 1 开始
        // 后16位表示当前时间段已使用的时间，从 0 开始
        vector<int> dp(1<<n, INT_MAX/2);
        dp[0] = 1<<16 | 0;
        for (int mask=0; mask<(1<<n); ++mask) {
            if (dp[mask] == INT_MAX/2) continue;
            int cnt = dp[mask] >> 16, used = dp[mask] % (1<<16);
            for (int i=0; i<n; ++i) {
                if ((mask >> i & 1) == 0) {
                    dp[mask|(1<<i)] = min(dp[mask|(1<<i)], inc(i, used)?(cnt+1)<<16 | tasks[i]:cnt<<16|tasks[i]+used);
                }
            }
        }
        return dp[(1<<n)-1]>>16;
    }
}; 