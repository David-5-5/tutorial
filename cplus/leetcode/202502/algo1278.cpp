#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 约束划分个数
class Solution {
public:
    int palindromePartition(string s, int k) {
        int n = s.size();

        auto count = [&](int l, int r) -> int {
            int h = (r-l) / 2, cnt = 0;
            for (int i=0; i<h; i++) {
                if (s[l+i] != s[r-1-i]) {
                    cnt += 1;
                }
            }
            return cnt;
        };

        vector<vector<int>> memo(n, vector<int>(k+1, -1));
        auto dfs = [&] (this auto&& dfs, int i, int j) ->int {
            if (j < 0) return INT_MAX/2;
            if (i == n)
                if (j == 0) return 0;
                else return INT_MAX/2;

            auto& res = memo[i][j];
            if (res != -1) return res;
            
            res = INT_MAX/2;
            for (int x = i; x<n; x++) {  // 不能超过 arr 长度
                res = min(res, count(i, x+1) + dfs(x+1, j-1));  
            }
            
            return res;
        };

        return dfs(0, k);         
    }
};