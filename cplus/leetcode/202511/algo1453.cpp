#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.2 圆
class Solution {
public:
    int numPoints(vector<vector<int>>& darts, int r) {
        // 自行解答
        const double EPS = 1e-6;  // 浮点数精度阈值
        int n = darts.size();

        auto findCenters = [&](vector<int>& v1, vector<int>& v2) -> vector<vector<double>>{
            vector<vector<double>> centers;
            
            // 提取坐标（int转double，避免整数截断误差）
            double x1 = v1[0], y1 = v1[1];
            double x2 = v2[0], y2 = v2[1];

            // 步骤1：计算两点的向量差与距离
            double dx = x2 - x1;
            double dy = y2 - y1;
            double d_sq = dx*dx + dy*dy;  // 距离的平方（减少开方次数）
            double d = sqrt(d_sq);        // 两点间实际距离

            // 特殊情况2：两点距离大于2r（无解）
            if (d >= 2*r + EPS) {
                return centers;
            }

            // 步骤2：计算线段v1v2的中点
            double mx = (x1 + x2) / 2.0;
            double my = (y1 + y2) / 2.0;

            // 特殊情况3：两点距离等于2r（圆心为中点，唯一解）
            if (fabs(d - 2*r) <= EPS) {
                centers.push_back({mx, my});
                return centers;
            }

            // 步骤3：计算2个圆心（d < 2r的普通情况）
            double half_d = d / 2.0;
            double h_sq = r*r - half_d*half_d;  // 圆心到线段v1v2的距离的平方
            if (h_sq < -EPS) {  // 精度误差导致的微小负值，视为无解
                return centers;
            }
            double h = sqrt(max(h_sq, 0.0));  // 确保非负

            // 垂直平分线的两个单位法向量（方向相反）
            double unit_x1 = -dy / d;
            double unit_y1 = dx / d;
            double unit_x2 = dy / d;
            double unit_y2 = -dx / d;

            centers.push_back({mx + unit_x1 * h, my + unit_y1 * h});
            centers.push_back({mx + unit_x2 * h, my + unit_y2 * h});

            return centers;
        };

        int ans = 1;
        for (int i=0; i<n-1; ++i) for (int j=i+1; j<n; ++j) {
            vector<vector<double>> centers = findCenters(darts[i], darts[j]);
            for (auto & c: centers) {
                int cnt = 0;
                for (int k=0; k<n; ++k) {
                    double dx = darts[k][0] - c[0], dy = darts[k][1] - c[1];
                    if (dx * dx + dy * dy - r * r <= EPS) cnt ++;
                }
                ans = max(ans, cnt);
            }

        }

        return ans;
      
    }
};