#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        // 自行解答 最小最大值 二分答案 2748
        int n = points.size();
        auto check = [&](long long upper) -> bool {
            // 都用 long long 类型，不然容易溢出越界
            long long prev = 0, left = m;
            for (int i=0; i<n; ++i) {
                // 最后一个，可以不进入单元
                if (1LL * prev * points[i] >= upper && i == n-1) return true;

                long long div = (upper + points[i] - 1) / points[i];
                prev = max(0LL, div - 1 - prev);
                left -= 1 + 2LL * prev;
                if (left < 0) return false;
            }
            return true;
        };

        int mx = ranges::max(points);
        long long l = 0L, r = 1LL * mx * m / n + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid)? l : r) = mid;
        }
        return l;
    }
};