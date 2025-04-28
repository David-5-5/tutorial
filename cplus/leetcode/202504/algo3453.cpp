#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  2.1 一维差分
class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        // 参考题解 固定循环次数
        long tot_area = 0;
        int max_y = 0;
        for (auto& s: squares) {
            tot_area += 1LL * s[2] * s[2];
            max_y = max(max_y, s[1] + s[2]);
        }

        auto check = [&] (double y) -> bool {
            double area = 0;
            for (auto& s:squares) {
                if (s[1] >= y) continue;

                area += s[2] * min((double)s[2], y - s[1]);
            }
            return (area * 2 >= tot_area);
        };

        double left = 0, right = max_y;
        for (int _=0; _<48; _++) {
            double mid = (left + right) / 2.0;
            (check(mid)? right:left) = mid;
        }

        return (left + right)/ 2;

    }
}; 