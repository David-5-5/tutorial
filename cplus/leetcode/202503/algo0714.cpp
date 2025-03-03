#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 状态机 DP - 买卖股票
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        // 自行解答
        int n = prices.size();

        vector<vector<int>> memo(n, vector<int>(2, INT_MIN/2));
        // i : index of prices
        // h : 0, no stock, 
        //     1, hold stock
        auto dfs = [&](this auto&& dfs, int i, int h) -> int{
            if (i == n-1) 
                if (h)
                    return max(0, prices[i]-fee);
                else return 0;
            
            auto& res = memo[i][h];
            if (res!=INT_MIN/2) return res;

            res = dfs(i+1, h); // 不操作

            if (h) {
                res = max(res, prices[i]-fee + dfs(i+1, 0));    // 买出股票
            } else {
                res = max(res, -prices[i] + dfs(i+1, 1));       // 卖入股票
            }
            return res;
        };

        return dfs(0, 0); 
    }
};