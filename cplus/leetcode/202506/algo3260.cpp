#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 输出具体方案
class Solution {
public:
    string largestPalindrome(int n, int k) {
        // 参考题解
        vector<int> pow10(n);

        pow10[0] = 1;           // 预处理，很关键
        for (int i=1; i<n; ++i)
            pow10[i] = pow10[i-1] * 10 % k;     
        
        string ans(n, 0);
        int m = (n+1) / 2;
        vector visit(m+1, vector<int>(k));
        auto dfs = [&](this auto&& dfs, int i, int j) -> bool {
            if (i == m) return j == 0;

            visit[i][j] = true;
            for (int d = 9; d>=0; d--) {
                int j2;
                if (n % 2 && i == m-1) // 正中间
                    j2 = (j + d * pow10[i]) % k;
                else
                    j2 = (j + d * (pow10[i] + pow10[n-i-1])) % k;
                
                if (!visit[i+1][j2] && dfs(i+1, j2)) {
                    ans[i] = ans[n-i-1] = '0' + d;
                    return true;
                }
            }
            return false;
        };
        dfs(0, 0);
        return ans;     
    }
};