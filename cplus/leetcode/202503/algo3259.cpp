#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 状态机 DP - 基础
class Solution {
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        // 自行解答
        int n = energyDrinkA.size();

        vector<vector<vector<long long>>> memo(n, vector<vector<long long>>(2, vector<long long>(2, -1)));

        // i 表示 当前可以获得的能量索引，
        // p 表示 上一个 A=0/B=1
        // t 表示 0, 上一个是p，t =1 表示 停顿一次，可以切换
        auto dfs = [&](this auto&& dfs, int i, int p, int t) -> long long{
            if (i < 0) return 0;

            auto& res = memo[i][p][t];
            if (res != -1) return res;

            res = 0;
            if (t == 1) {
                res = (p==0?energyDrinkB[i]:energyDrinkA[i]) + dfs(i-1, 1-p, 0);
            } else {
                res = (p==0?energyDrinkA[i]:energyDrinkB[i]) + dfs(i-1, p, 0);
                res = max(res, dfs(i-1, p, 1));     // 停止一天
            }
            return res;
        };

        return max(dfs(n-1, 0, 0), dfs(n-1,1,0));       
    }
};