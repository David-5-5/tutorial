#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        // 自行解答 记忆化搜索 状态压缩
        int mx = maxChoosableInteger, dt = desiredTotal;

        if (mx * (mx+1) / 2 < desiredTotal) return false;
    
        vector<int> memo(1<<mx, -1);
        auto dfs = [&](this auto&& dfs, int s) -> bool {
            int sum = 0;            // 当前状态的整数和
            for (int i=0; i<mx; ++i) {
                if (s >> i & 1) sum += (i+1);
            }
            
            auto& res = memo[s];
            if (res != -1) return res;
            res = 0;
            
            // 遍历所有状态，寻找最优解
            for (int i=0; i<mx; ++i) {      
                if ((s >> i & 1) == 0) {
                    // 情况1 ： 整数和增加当前选择 (i+1) 返回 true
                    if (sum + i + 1 >= dt) return res=1;
                    // 情况2 ： 选择当前状态后，若对手失败，则获胜，返回 true
                    if (!dfs(s|1<<i)) return res=1;
                }
            }
            // 遍历所有状态后未获胜，返回 false
            return res=0;   // 返回失败
        };
    
        return dfs(0);   
    }

};