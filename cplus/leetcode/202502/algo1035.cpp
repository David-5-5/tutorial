#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列（LCS）
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        // 自行解答
        int m = nums1.size(), n = nums2.size();

        vector<vector<int>> memo(m, vector<int>(n, -1));

        function<int(int, int)> dfs = [&] (int i, int j) -> int {
            if (i < 0 || j < 0) return 0;

            auto& res = memo[i][j];
            if (res != -1) return res;

            if (nums1[i] == nums2[j]) {
                res = 1 + dfs(i-1, j-1);
            } else {
                res = max(dfs(i, j-1), dfs(i-1, j));
            }

            return res;

        };
        
        return dfs(m-1, n-1);
    }
};