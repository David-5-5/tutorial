#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.5 因子
class Solution {
public:
    int countPairs(vector<int>& nums, int k) {
        // 非暴力做法 调和级数 原题数据范围较小，可以暴力 O(N^2)
        // i * j | k => i | k/gcd(k, j)
        unordered_map<int, vector<int>> groups;
        for (int i=0; i<nums.size(); ++i) groups[nums[i]].push_back(i);

        int ans = 0;
        for (auto [key, grp]: groups) {

            if (grp.size() == 1) continue;
            int mx = ranges::max(grp); vector<int> target(mx+1);

            unordered_map<int, int> num_cnt;
            for (auto v:grp) num_cnt[k / gcd(k, v)] ++;
            for (auto [x, c]: num_cnt) {
                target[0] += c;   // 本期不同于 2183 的关键点
                for (int y = x; y<=mx; y+=x) target[y] += c;
            }
            int res = 0;
            for (const auto& x: grp) {
                res += target[x];                  // 全集
                if ((x * x) % k == 0) res --;      // i == j
            }
            ans += res/2;
        }
        return ans;     
    }
};