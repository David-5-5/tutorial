#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.1 点、线
class Solution {
public:
    vector<int> bestLine(vector<vector<int>>& points) {
        // 自行解答，思想类似于 149
        int n = points.size(), mx_cnt=0; vector<int> ans(2, n);
        for (int i=0; i<n-1; ++i) {
            // key is slope , value is count of the slope
            // i is the origin
            unordered_map<double, set<int>> k_cnt;
            for (int j=i+1; j<n; ++j) {
                double slope = DBL_MAX;
                if (points[i][0]!=points[j][0]) { // x_i != x_j
                    slope = (1.0 * points[j][1] - points[i][1])/(1.0 * points[j][0] - points[i][0]);
                }
                k_cnt[slope].insert(j);
            }
            for (auto& [_, points]:k_cnt) {
                if (points.size() > mx_cnt) {
                    mx_cnt = points.size(); ans[0] = i; ans[1] = *points.begin();
                } else if (points.size() == mx_cnt) {
                    if (ans[0] == i) ans[1] = min(ans[1], *points.begin());
                }
            }

        }
        return ans;        
    }
};