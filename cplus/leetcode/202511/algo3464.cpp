#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 五、三指针
class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> arr;
        for (auto p: points) {
            auto x = p[0], y = p[1];
            if (x == 0) arr.push_back(y);
            else if (y == side) arr.push_back(1LL * side + x);
            else if (x == side) arr.push_back(3LL * side - y);
            else if (y == 0) arr.push_back(4LL * side - x);
        }

        sort(arr.begin(), arr.end());

        auto check = [&] (int limit) -> bool {
            for (long long x: arr) {
                long long end = x + 4LL * side - limit, cur = -1;                
                for (int _=0; _<k-1; _++) {
                    auto it = ranges::lower_bound(arr, x + limit);
                    if (it == arr.end() || *it > end) {
                        x = -1; break;
                    } x = *it;
                }
                if (x > 0) return true;
            }

            return false;
        };

        long long left = 0, right = 4LL * side / k  + 1;
        while (left + 1 < right) {
            auto mid = (left + right) / 2;
            (check(mid)? left: right ) = mid;
        }
        return left;
    }
};