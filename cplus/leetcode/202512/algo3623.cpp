#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        // 自行解答
        const int mod = 1e9 + 7;
        unordered_map<int, int> y_cnt;
        for (auto & p : points) y_cnt[p[1]] ++;

        int ans = 0, i=1, n = points.size(); long long pre = 0;
        for (auto &[_, c] : y_cnt) {
            if (c > 1) {
                int comb = 1LL * c * (c-1) / 2 % mod;
                ans = (pre * comb + ans) % mod;
                pre = (pre + comb) % mod;
            }
        }
        return ans; 

    }


};

