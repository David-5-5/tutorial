#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.5 因子
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        // 自行解答
        int mx = ranges::max(nums1);
        vector<int> cnt(mx+1);
        unordered_map<int, int> n1_cnt, n2_cnt;
        for (auto v:nums1) n1_cnt[v] ++;
        for (auto v:nums2) n2_cnt[v] ++;

        long long ans = 0;
        for (auto [v, c]: n2_cnt)  {
            auto x = k * v;
            for (int y=x; y<=mx; y+=x) cnt[y] += c;
        }

        for (auto [k, v]: n1_cnt) ans += (long long)v * cnt[k];
        return ans;  
    }
};