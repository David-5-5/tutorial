#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.2 圆
class Solution {
public:
    int numPoints(vector<vector<int>>& darts, int r) {
        int ans = 0, n = darts.size();
        for (int i = 0; i < n-1; ++i) {
            int xi = darts[i][0], yi = darts[i][1], res = 1;
            for (int j=i+1; j < n; ++j) {   
                int xj = darts[j][0], yj = darts[j][1];
                if (pow(xi-xj, 2) + pow(yi-yj, 2) <= pow(2*r, 2)) res ++;

            }
            ans = max(ans, res);
        }
        return ans;
    }
};