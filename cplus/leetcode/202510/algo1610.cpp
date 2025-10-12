#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        // 学习极角计算
        auto cal_degree = [](int x, int y) -> double {
            double rad = atan2(y, x);           // (-π, π]
            double deg = rad * 180.0 / M_PI;    // (-180°, 180°]
            if (deg < 0)  deg += 360.0;
            return deg;                         // [0, 360)
        };

        auto x0 = location[0], y0 = location[1];
        int locs = 0;
        vector<double> deg_list;
        for (auto& p: points) {
            if (x0 == p[0] && y0 == p[1]) locs ++;
            else deg_list.push_back(cal_degree(p[0]-x0, p[1]-y0));
        }
        
        int n = deg_list.size(), l = 0, ans = 0;
        sort(deg_list.begin(), deg_list.end());
        for (int i=0; i<n; ++i) deg_list.push_back(deg_list[i]+360);
        
        for (int r=0; r<deg_list.size(); ++r) {
            while (deg_list[l] + angle < deg_list[r]) l ++;
            ans = max(ans, r - l + 1);
        }
        return ans + locs;

    }
};