#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数
class Solution {
private:
    double radius, x_center, y_center;
public:
    Solution(double radius, double x_center, double y_center) {
        this->radius = radius, this->x_center = x_center, this->y_center = y_center;
    }
    
    vector<double> randPoint() {
        while (true) {
            double x = x_center-radius + 2 * radius * (double)rand() / RAND_MAX;
            double y = y_center-radius + 2 * radius * (double)rand() / RAND_MAX;
            double dx = x - x_center, dy = y - y_center;
            if (dx * dx + dy * dy - radius * radius < 1e-9) {   // 精度要高
                return {x, y};
            }
        }
    }
};
