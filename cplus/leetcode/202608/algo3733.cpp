#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumTime(vector<int>& d, vector<int>& r) {
        // 自行解答 数学容斥原理 + 二分
        auto l = lcm(r[0], r[1]);

        auto check = [&](long long x) -> bool {
            long long d1 = d[0], d2 = d[1];

            auto blocked = x / l;               // 两个无人机都不可用的时间
            auto avail_1 = x / r[1] - blocked;  // 仅无人机 1 可用的时间
            auto avail_2 = x / r[0] - blocked;  // 仅无人机 2 可用的时间
            auto avail = x - avail_1 - avail_2 - blocked;
            // 无人机首先使用专属的时间
            d1 -= min(d1, avail_1); d2 -= min(d2, avail_2);
            return d1 + d2 <= avail;
        };

        long long left = 1, right = 4LL * (d[0] + d[1]);
        while (left + 1 < right) {
            auto mid = (left + right) / 2;
            (check(mid) ?right : left) = mid;
        }

        return right;
    }
};