#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minInitialStrength(vector<int>& monsters, vector<vector<int>>& boosts) {
        int n = monsters.size();
        vector<long long> bonus(n);
        for (auto & b: boosts) {
            auto l = b[0], r = b[1], v = b[2];
            bonus[l] += v;
            if (r+1 < n) bonus[r+1] -= v;
        }
        for (int i=1; i<n; i++) bonus[i] += bonus[i-1]; 

        auto check = [&](long long init) -> bool {
            for (int i=0; i<n; i++) {
                if (init + bonus[i] < monsters[i]) return false;
                init = max(0LL, init - monsters[i]);
            }

            return true;
        };

        long long l = -1, r = 5 * 1e13 + 1;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            (check(mid)?r:l) = mid;
        }

        return r;
    }
};