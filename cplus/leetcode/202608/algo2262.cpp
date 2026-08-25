#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {

        auto check = [&](int val) -> bool {
            long long res = 0;
            for (auto v: candies) {
                res += v / val;
            }
            return res >= k;
        };
        int l = 0, r = ranges::max(candies) + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid) ? l : r) = mid;
        }
        return l;   
    }
};