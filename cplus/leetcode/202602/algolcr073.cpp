#include <bits/stdc++.h>
using namespace std;

// 同 875
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // 自行解答
        auto check = [&] (int mid) -> bool {
            long long res = 0;
            for (auto & x: piles) {
                res += (x + mid - 1) / mid;
            }
            
            return res <= h;
        };

        int l = 0, r = ranges::max(piles) + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid) ? r : l) = mid;
        }
        return r;
    }
};