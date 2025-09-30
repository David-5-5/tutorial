#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.6 最大公约数（GCD）
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        // 自行解答，暴力求解斜率，都不敢这么做
        int n = points.size(), ans = 0;
        for (int i=0; i<n-1; ++i) {
            // key is slope , value is count of the slope
            // i is the origin
            unordered_map<double, int> k_cnt;
            for (int j=i+1; j<n; ++j) {
                double slope = DBL_MAX;
                if (points[i][0]!=points[j][0]) { // x_i != x_j
                    slope = (1.0 * points[j][1] - points[i][1])/(1.0 * points[j][0] - points[i][0]);
                }
                k_cnt[slope] ++;
                ans = max(ans, k_cnt[slope]);
            }

        }
        return ans+1;
    }

};