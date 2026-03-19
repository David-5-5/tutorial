#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.8 相邻不同
class Solution {
public:
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        // 自行解答 2666
        const int mod  = 1e9 + 7;
        long long mx = ranges::max(nums), mn = ranges::min(nums);
        int n = nums.size(); 
        auto diff = mx - mn; if (diff == 0) return 0;
        long long totalInc = 0; // Total increment to max value
        for (auto & v: nums) totalInc += (mx - v);

        if (cost1 * 2 <= cost2) return totalInc * cost1 % mod;
        
        auto count = [&](long long n, long long m) -> pair<long long, long long> {
            long long v2 = min(n/2, n - m);         // 相邻不同问题二公式
            long long v1 = max((n+1)/2, m) - v2;    // 相邻不同问题三公式
            return {v1, v2};
        };
        auto [use1, use2] = count(totalInc, diff);
        long long ans = use2 * cost2 + use1 * cost1;

        if (n > 2) {    //
            // 最大化 v2 ，使 v1 最小， n/2 == n - m, 即 n = 2 * (n - m) (1)
            // 带入变量 x 表示最大值增量 n = totalInc + n * x, m = diff + x
            // 代入 (1) totalInc + n * x = 2 * (totalInc + n * x - diff - x) (2)
            // 整理 (2) 得到 x = (2 * diff - totalInc) / (n - 2)
            // f = floor(x), c = ceil(x)
            auto f = (2 * diff - totalInc) / (n - 2), c= (2 * diff - totalInc + n - 3) / (n - 2);
            set<int> inc;       // increase the value of mx
            // 如果 n 为偶数，f, f+1, c, c+1 不会改变奇偶性，但由于计算量很小，无需过多判断，代码简洁
            inc.insert(1);  // tot is odd, tot + n may be even, use1 is zero.
            inc.insert(f), inc.insert(f+1); // tot + f*n or tot + (f+1)*n may be even, use1 -> 0.
            inc.insert(c), inc.insert(c+1); // tot + c*n or tot + (c+1)*n may be even, use1 -> 0.
            for (auto f: inc) {
                if (f <= 0 ) continue;
                auto v1 = count(totalInc + n * f, diff+f);
                ans = min(ans, v1.first * cost1 + v1.second * cost2);
            }
        }

        return ans % mod;
    }

    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        // tie usage
        const int mod  = 1e9 + 7;
        long long mx = ranges::max(nums), mn = ranges::min(nums);
        int n = nums.size(); // m is count of mx
        auto diff = mx - mn; if (diff == 0) return 0;
        long long totalInc = 0; // Total increment to max value
        for (auto & v: nums) totalInc += (mx - v);

        if (cost1 * 2 <= cost2) return totalInc * cost1 % mod;
        
        auto count = [&](long long n, long long m) -> pair<long long, long long> {
            long long v2 = min(n/2, n - m);
            long long v1 = max((n+1)/2, m) - v2;
            return {v1, v2};
        };
        long long use1, use2;
        tie(use1, use2) = count(totalInc, diff);
        long long ans =  use1 * cost1 + use2 * cost2;

        if (n > 2) {    // 
            // tot/2 == tot-cnt -> f, c,
            set<int> inc_set;       // increase the value of mx
            // 如果 n 为偶数，f, f+1, c, c+1 不会改变奇偶性，但由于计算量很小，无需过多判断，代码简洁
            if (2 * diff <= totalInc)
                inc_set.insert(1);  // tot is odd, tot + n may be even, use1 is zero.
            else {
                auto floor = (2 * diff - totalInc) / (n - 2), ceil = (2 * diff - totalInc + n - 3) / (n - 2);
                inc_set.insert(floor), inc_set.insert(floor+1); // tot + f*n or tot + (f+1)*n may be even, use1 -> 0.
                inc_set.insert(ceil), inc_set.insert(ceil+1); // tot + c*n or tot + (c+1)*n may be even, use1 -> 0. 
            }
            for (auto inc: inc_set) {
                tie(use1, use2) = count(totalInc + n * inc, diff+inc);
                ans = min(ans, use1 * cost1 + use2 * cost2);
            }
        }
        return ans % mod;
    }    
};