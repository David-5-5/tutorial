#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最优划分
class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        // 自行解答
        int n = books.size();

        vector<int> memo(n, -1);
        auto dfs = [&] (this auto&& dfs, int i) {
            if (i == n) return 0;

            auto& res = memo[i];
            if (res != -1) return res;
            
            res = INT_MAX;
            int thick = 0, height = 0;
            for (int j = i; j<n; j++) {
                thick += books[j][0];
                height = max(height, books[j][1]);
                if (thick <= shelfWidth) {
                    res = min(res, height + dfs(j+1));
                } else break;
            }
            
            return res;
        };

        return dfs(0);            
    }
};