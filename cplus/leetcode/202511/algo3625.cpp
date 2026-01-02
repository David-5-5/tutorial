#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.3 矩形、多边形
class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<double, map<double, int>> cnt; // 斜率 -> 截距 -> 个数
        unordered_map<int, map<double, int>> cnt2; // 中点 -> 斜率 -> 个数

        int n = points.size();

        for (int i = 0; i<n-1; ++i) {
            int x = points[i][0], y = points[i][1];
            for (int j = i+1; j<n; ++j) {
                int x2 = points[j][0], y2 = points[j][1];
                int dx = x - x2, dy = y - y2;
                double k = dx? 1.0 * dy / dx: DBL_MAX;
                double b = dx? 1.0 * (y * dx - x * dy) / dx : x;
                cnt[k][b] ++;
                int mid = (x + x2 + 2000) << 16 | (y + y2 + 2000); // x + x2 + 2000 > 0
                cnt2[mid][k] ++;
            }
        }
        int ans = 0;
        for (auto & [_, m]:cnt) {
            int pres = 0;
            for (auto& [_, c]: m) {
                // c 是一对平行边的方案数，区别与 3623 点的数量，c*(c-1)/2
                ans += pres * c; pres += c;
            }
        }
        // 找平行四边形还需要进一步理解
        for (auto & [_, m]: cnt2) {
            int pres = 0;
            for (auto & [_, c] : m) {
                ans -= pres * c; pres += c;
            }
        }

        return ans;

    }
};