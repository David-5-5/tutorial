#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        // 参考题解 !!!代码很短，思维很难!!!
        int sum = accumulate(dist.begin(), dist.end(), 0);

        if ((sum+speed-1)/speed > hoursBefore) return -1;
        
        int n = dist.size();
        vector<vector<int>> memo(n, vector<int>(n, -1)); // -1 表示没有计算过
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (j < 0) { // 递归边界
                return 0;
            }
            auto& res = memo[i][j]; // 注意这里是引用
            if (res != -1) { // 之前计算过
                return res;
            }
            // 核心代码，也就两行
            // + speed - 1 上取整
            res = (dfs(i, j - 1) + dist[j] + speed - 1) / speed * speed;    // 不跳过
            if (i) res = min(res, dfs(i - 1, j - 1) + dist[j]);             // 跳过
            return res;

        };
            
        //  枚举 i 从小到大
        for (int i = 0; ; i++) {
            if (dfs(i, n - 2) + dist[n - 1] <= (long long) speed * hoursBefore) {
                return i;
            }
        }

    }
};