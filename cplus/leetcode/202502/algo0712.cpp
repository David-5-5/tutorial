#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列（LCS）
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size(), n = s2.size();

        // LCS 模板 记忆化搜索 时间复杂度 O(mn)/O(n^2)
        vector<vector<int>> memo(m, vector<int>(n, -1));
        function<int(int, int)> dfs = [&](int i, int j) ->int {
            if (i < 0 || j < 0) {
                int val = 0;
                while (i >= 0) {
                    val += s1[i]; i--; // s1[i] char -> int 
                }
                while (j >= 0) {
                    val += s2[j]; j--;
                }
                return val;
            }

            auto& res = memo[i][j];
            if (res != -1) return res;

            if (s1[i] == s2[j]) return res = dfs(i-1, j-1);
            else return res = min(dfs(i-1, j) + s1[i], dfs(i, j-1) + s2[j]);

        };

        return dfs(m-1, n-1);
    }
};