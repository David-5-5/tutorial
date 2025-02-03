#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 网格图 DP - 基础
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        // 自行解答
        int n = matrix.size();

        for (int i=1; i<n; i++) {
            for (int j=0; j<n; j++) {
                int left = (j==0?INT_MAX:matrix[i-1][j-1]);
                int right = (j>=n-1?INT_MAX:matrix[i-1][j+1]);
                matrix[i][j] += min(left, min(right, matrix[i-1][j]));
            }
        }

        return *min_element(matrix[n-1].begin(), matrix[n-1].end());      
    }
};