#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 网格图 DP - 基础
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> cur = {triangle[0][0]};
        int rows = triangle.size();
        for (int i=1; i<rows; i++) {
            int m = triangle[i].size();
            vector<int> next(m);
            for (int j=0; j<m; j++) {
                int left = (j-1)>=0 ? cur[j-1]: INT_MAX;
                int right = (j<m-1) ? cur[j]: INT_MAX;
                next[j] = triangle[i][j] + min(left, right);
            }
            cur = next;
        }

        return *min_element(cur.begin(), cur.end());

    }
};