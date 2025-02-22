#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        // 引用 300 LIS 方案
        vector<int> dp;
        vector<map<int, int>> cnt;

        auto f = [&](int i, int x) -> int {
            int res = 0;
            if (i-1 < 0)  return 1;

            for (auto it = cnt[i-1].begin(); it!= cnt[i-1].end(); ++it) {
                if (it->first < x) res += it->second;
            }
            return res;
        };  

        for (auto& x : nums) {
            auto it = ranges::lower_bound(dp, x);
            if (it != dp.end()) {
                *it = x,                // c++ iterator usage
                cnt[it-dp.begin()][x] += f(it-dp.begin(), x);
            }        
            else {
                map<int, int> cnt_map;
                cnt_map[x] = f(it-dp.begin(), x);

                cnt.push_back(cnt_map);
                dp.push_back(x);
            }
        }

        int ans = 0;
        for (auto it = cnt.back().begin(); it!= cnt.back().end(); ++it) {
            ans += it->second;
        }        

        return ans;
    }
};