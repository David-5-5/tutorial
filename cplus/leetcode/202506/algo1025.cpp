#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 15. 概率/期望 DP
class Solution {
public:
    bool divisorGame(int n) {
        // 自行解答 DP
        vector<int> memo(n+1, -1);
        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i == 1) return 0;
            
            auto& res = memo[i];
            if (res != -1) return res;
            res = 0;
            for (int div=1; div<i; ++div) {
                if (i % div == 0 && !dfs(i-div)) return res = 1;
            }
            return res;
        };
        
        return dfs(n);
    }
};