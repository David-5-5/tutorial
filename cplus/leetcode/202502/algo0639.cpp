#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最优划分
class Solution {
public:
    int numDecodings(string s) {
        // 自行解答
        int n = s.size();
        int mod = 1e9 + 7;

        // 计算 cnt 比较繁琐 
        // 不过，官方题解也类似这样
        auto cnt = [&] (int i, int j) -> int {
            if (j == 1 && s[i] == '*') {
                return 9;
            } else if (j == 2) {
                // * 代表 1 ~ 9 ，两位的时候 不包括 10, 20
                if (s[i] == '*' && s[i+1] == '*') return 15; // 11~19,21~26 
                else if (s[i] == '*' && s[i+1]-'0' <=6) return 2;
                else if (s[i+1] == '*' && s[i] == '1') return 9;
                else if (s[i+1] == '*' && s[i] == '2') return 6;
                else if (s[i] == '2' && s[i+1]-'0' > 6 || s[i]-'0' > 2 ) return 0;
            }
            return 1;
        };

        vector<int> memo(n, -1);
        auto dfs = [&] (this auto&& dfs, int i) {
            if (i == n) return 1;

            auto& res = memo[i];
            if (res != -1) return res;
            
            res = 0;
            if (s[i] == '0') return res = 0; // 不能有前导 0
            res = (res + (long) cnt(i, 1) * dfs(i+1)) % mod;
            if (i+2 <= n) res = (res +  (long)cnt(i, 2) * dfs(i+2)) % mod;
            
            return res;
        };

        return dfs(0);
    }
};