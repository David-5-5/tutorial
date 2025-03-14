#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最优划分
class Solution {
public:
    string minCostGoodCaption(string caption) {
        // 参考题解
        int n = caption.size();
        if (n<3) return "";

        vector<array<int, 26>> dp(n+1);     // 记录最小修改次数
        vector<array<int, 26>> nxt(n+1);    //记录转移来源
        vector<int> minj(n+1);              // f[i][minj[i]] = min(f[i][k])  0 <= k < 26
        
        for (int i=n-1; i>=0; i--) {
            int mn = INT_MAX;   
            for (int j=0; j<26; j++) {  // 枚举字母
                // 状态转移方程
                int res = dp[i + 1][j] + abs(caption[i] - 'a' - j);
                int res2 = i <= n - 6 ? dp[i + 3][minj[i + 3]] + abs(caption[i] - 'a' - j) + abs(caption[i + 1] - 'a' - j) + abs(caption[i + 2] - 'a' - j) : INT_MAX;
                
                // 为输出最小字典序结果
                if (res2 < res || res2 == res && minj[i + 3] < j) {
                    res = res2;
                    nxt[i][j] = minj[i + 3]; // 记录转移来源
                } else {
                    nxt[i][j] = j; // 记录转移来源
                }
                dp[i][j] = res;
                if (res < mn) {
                    mn = res;
                    minj[i] = j; // 记录最小的 dp[i][j] 中的 j 是多少
                }
            }
        }
        string ans(n, 0);
        int i = 0, j = minj[0];
        while (i < n) {
            ans[i] = 'a' + j;
            int k = nxt[i][j];
            if (k == j) {
                i++;
            } else {
                ans[i + 2] = ans[i + 1] = ans[i];
                i += 3;
                j = k;
            }
        }
        return ans;

        
    }
};