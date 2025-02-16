#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列（LCS）
class Solution {
public:
    int minDistance(string word1, string word2) {
        
        int m = word1.size(), n = word2.size();

        vector<vector<int>> memo(m, vector<int>(n, -1));
        function<int(int, int)> dfs = [&](int i, int j) ->int {
            if (i < 0 || j < 0) return 0;

            auto& res = memo[i][j];
            if (res != -1) return res;

            if (word1[i] == word2[j]) return res = dfs(i-1, j-1) + 1;
            else return res = max(dfs(i-1, j), dfs(i, j-1));

        };

        return m + n - 2 * dfs(m-1, n-1);
    }
};