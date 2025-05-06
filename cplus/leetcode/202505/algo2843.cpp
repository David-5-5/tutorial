#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 数位 DP
class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        // 非暴力解法
        string s_low = to_string(low), s_high = to_string(high);
        int n = s_high.length(), diff = n - s_low.length();
        
        unordered_map<int, int> memo;
        // vector memo(n, vector(diff + 1, vector<int>(n / 2 * 9 + 1, -1)));
        // 没有找到 start，参考题解
        auto f = [&](this auto&& f, int i, int start, int sum, bool is_low, bool is_high) -> int {
            if (sum < 0) return 0;
            if (i == n) return sum == 0;

            long mask = (long)i << 16 | sum << 2 | is_low << 1 | is_high;    // 10^62

            if (start!=-1 && memo.count(mask)) return memo[mask];
            // if (start != -1 && !is_low && !is_high && memo[i][start][sum] != -1) {
            //     return memo[i][start][sum];
            // }

            int lo = is_low && i >= diff? s_low[i-diff] - '0' : 0;
            int hi = is_high? s_high[i] - '0' : 9;
            
            // 如果前面没有填数字，且剩余数位个数是奇数，那么当前数位不能填数字
            if (start < 0 && (n - i) % 2) {
                // 如果必须填数字（lo > 0），不合法，返回 0
                return lo > 0 ? 0 : f(i + 1, start, sum, true, false);
            }


            bool is_left = start < 0 || i < (start + n) / 2;
            int res = 0;
            for (int d=lo; d<=hi; ++d) {
                res += f(i+1, start<0&&d>0 ? i : start, sum + (is_left ? d : -d), is_low && d==lo, is_high && d==hi);
            }
            if (start!=-1) memo[mask] = res;
            // if (start != -1 && !is_low && !is_high) {
            //     memo[i][start][sum] = res;
            // }            
            return res;

        };

        return f(0, -1, 0, true, true);
    }
};