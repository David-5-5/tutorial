#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最优划分
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();

        vector<int> memo(n, -1);
        auto dfs = [&] (this auto&& dfs, int i) {
            if (i == n) return 1;

            auto& res = memo[i];
            if (res != -1) return res;
            
            res = 0;
            if (s[i] == '0') return res = 0; // 不能有前导 0
            res += dfs(i+1);
            if (i+2 <= n && stoi(s.substr(i, 2)) <= 26) res += dfs(i+2);
            
            return res;
        };

        return dfs(0);
    }
};