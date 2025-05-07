#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 数位 DP
class Solution {
public:
    int beautifulNumbers(int l, int r) {
        string sl = to_string(l), sr = to_string(r);
        int n = sr.length(), diff = n - sl.length();

        unordered_map<long, int> memo;
        auto f = [&](this auto&& f, int mul, int sum, int i, 
                bool is_low, bool is_high, bool is_num) ->int {
            
            if (i == n) return is_num && mul % sum == 0;
            long mask = (long)mul << 14 | sum << 7 | i << 3 | is_low << 2 | is_high << 1 | is_num;

            if (memo.count(mask)) return memo[mask];
            int lo = is_low && i >= diff? sl[i-diff] - '0' : 0;
            int hi = is_high? sr[i] - '0' : 9;
            
            int res = 0;
            for (int d=lo; d<=hi; ++d) {
                if (!is_num && d == 0) res += f(mul, sum, i+1, is_low && d==lo, is_high && d==hi, false);
                else res += f(mul*d, sum+d, i+1, is_low && d==lo, is_high && d==hi, true);
            }
            return memo[mask] = res;

        };

        return f(1, 0, 0, true, true, false); 
    }
};