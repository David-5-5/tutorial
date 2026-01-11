#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 六、状态机 DP 6.1 买卖股票
class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        // translate from python by doubao
        int n = prices.size();

        vector memo(3, vector(n, vector<long long>(k+1, -1)));

        function<long long(int, int, int)> dfs = [&](int c, int i, int j) -> long long {
            if (j == 0) return 0;            
            if (i < 0)  return (c != 0) ? (LLONG_MIN / 2) : 0;

            auto & res = memo[c][i][j];
            if (res != -1)  return res;

            long long p = prices[i];
            if (c == 0) {
                res = max({ dfs(0, i - 1, j), dfs(1, i - 1, j) + p,  dfs(2, i - 1, j) - p});
            } else if (c == 1) { res = max( dfs(1, i - 1, j), dfs(0, i - 1, j - 1) - p );
            } else {  res = max( dfs(2, i - 1, j), dfs(0, i - 1, j - 1) + p );
            }
            return res;
        };

        long long ans = dfs(0, n-1, k);
        return max(ans, 0LL);
    }
};