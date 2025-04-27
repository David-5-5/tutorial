#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        int mx = maxChoosableInteger, dt = desiredTotal;

        if (mx * (mx+1) / 2 < desiredTotal) return false;
    
        vector<int> memo(1<<mx, -1);
        auto dfs = [&](this auto&& dfs, int s) -> bool {
            int sum = 0;
            for (int i=0; i<mx; ++i) {
                if (s >> i & 1) sum += (i+1);
            }
            
            auto& res = memo[s];
            if (res != -1) return res;
            res = 0;
    
            for (int i=0; i<mx; ++i) {
                if ((s >> i & 1) == 0) {
                    if (sum + i + 1 >= dt) return res=1;
                    if (!dfs(s|1<<i)) return res=1;
                }
            }
    
            return res=0;
        };
    
        return dfs(0);   
    }

};