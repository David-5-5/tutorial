#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int sum = accumulate(weights.begin(), weights.end(), 0);
        int n = weights.size();

        auto check = [&](int limit) -> bool {
            int res = 1, cur = 0;
            for (int i=0; i<n; i++) {
                if (weights[i] > limit) return false;
                if (cur + weights[i] > limit) {
                    res ++; cur = 0;
                }
                cur += weights[i];
            }
            return res <= days;
        };
        
        int l = -1, r = sum + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid) ? r : l) = mid;
        }
        return r;
    }
};