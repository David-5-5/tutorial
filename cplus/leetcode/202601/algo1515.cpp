#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        // 参考题解，梯度下降法
        double eps = 1e-7, alpha = 1, decay = 1e-3;

        int n = positions.size(); int batchSize = n;
        double x = 0.0, y = 0.0;
        for (const auto& pos : positions) {
            x += pos[0]; y += pos[1];
        }
        x /= n; y /= n;
        auto distance = [&] (double xc, double yc) -> double {
            double ans = 0;
            for (const auto & pos: positions)
                ans += sqrt((pos[0] -xc) * (pos[0] -xc) + (pos[1] -yc) * (pos[1] -yc));
            return ans;
        };

        mt19937 gen{random_device{}()};
        while (true) {
            shuffle(positions.begin(), positions.end(), gen);
            double xPrev = x, yPrev = y;
            for (int i = 0; i<n; i+=batchSize) {
                int j = min(i+batchSize, n);
                double dx = 0.0, dy = 0.0;
                for (int k=i; k<j; ++k) {
                    const auto& pos = positions[k];
                    double denom = sqrt((x-pos[0])*(x-pos[0]) + (y-pos[1])*(y-pos[1])) + eps;
                    dx += (x-pos[0])/ denom;
                    dy += (y-pos[1])/ denom;
                }
                x -= alpha * dx; y -= alpha * dy;
            }
            alpha *= (1.0 -decay);
            if (sqrt((x - xPrev) * (x - xPrev) + (y - yPrev) * (y - yPrev)) < eps) {
                break;
            }
        }

        return distance(x, y);
    }
};