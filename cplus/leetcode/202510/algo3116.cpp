#include <bits/stdc++.h>
using namespace std;


// 数学算法 - 组合数学 - 2.5 贡献法
class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        // 自行解答，需要将 878，1201 一般化
        int n = coins.size(), mask = 1<<n;
        // 必须设置为 long long, 爆 int
        unordered_map<int, vector<long long>> lcms;
        for (int i=1; i<mask; ++i) {
            long long l = 1;    
            for (int j=0; j<n; ++j) if ((i>>j) & 1) {
                l = lcm(l, coins[j]);   
            }
            lcms[__builtin_popcount(i)].push_back(l);
        }

        auto check = [&](long long mid) -> bool {
            long long cnt = 0;
            for (auto& [k, v]: lcms) for (auto& l:v) {
                cnt += (k%2?1:-1) * mid / l;
            }

            return cnt >= k;
        };

        long long left = ranges::min(coins)-1, right = 1LL * ranges::max(coins) * k;
        while (left+1 < right) {
            long long mid = (right + left)/2;
            (check(mid)?right:left) = mid;
        }
        long long ans = 0;
        for (auto& [_, v]: lcms) for (auto& l:v) {
            ans = max(ans, 1LL * (right/l) * l);
        }
        
        return ans;       
    }
};