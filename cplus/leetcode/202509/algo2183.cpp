#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.5 因子
class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        // 自行解答
        unordered_map<int, int> cnt; long long ans = 0;

        for (const auto& v: nums) {
            ans += cnt[k / gcd(v, k)];
            for (int i = 1; i*i<= v; ++i) if (v % i == 0){
                cnt[i] ++;
                if (i * i != v) cnt[v/i] ++;
            }
        }
        return ans;
    }

    long long countPairs2(vector<int>& nums, int k) {
        // 参考题解
        int mx = ranges::max(nums); vector<int> target(mx+1);

        // 后续类似于 3164
        unordered_map<int, int> num_cnt;
        for (auto v:nums) num_cnt[k / gcd(k, v)] ++;

        for (auto [x,c]:num_cnt) {
            for (int y = x; y<=mx; y+=x) target[y] +=c;
        }
        long long ans = 0;

        // reapted cnt
        for (const auto& x: nums) {
            ans += target[x];                       // 全集
            if ((1L * x * x) % k == 0) ans --;      // i == j
        }
        return ans / 2;                             //  i < j
    }    
};