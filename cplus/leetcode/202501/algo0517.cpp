#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 思维题 - 从特殊到一般
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        // 2025.1 复习 自行解答
        int ans = 0,  n = machines.size();        
        // 计算前缀和 模板
        vector<int> presum(n+1);
        for (int i=0; i<n; i++) {
            presum[i+1] = presum[i] + machines[i];
        }
        if (presum[n] % n) return -1;
        int unit = presum[n] / n;

        // 枚举每个数  计算其向左/向右, 移出/移入的数量，分四种情况：
        // 1, <-  x  <- 2, ->  x  ->  3, ->  x  <-      1, 2, 3 取最大值可同时进行
        // 4, <-  x  ->                        取和
        for (int i=0; i<n; i++) {
            if (i == 0 || i == n-1)
                ans = max(ans, abs(unit-machines[i]));
            else {
                int l = presum[i] - unit * i;
                int r = presum[n] - presum[i+1] - unit * (n-i-1);

                if (l < 0 && r < 0) ans = max(ans, abs(l)+abs(r));
                else ans = max(ans, max(abs(l),abs(r)));
            }
        }

        return ans;
    }
};