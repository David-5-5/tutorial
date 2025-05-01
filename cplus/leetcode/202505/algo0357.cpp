#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 数位 DP
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        // 自行解答 数位 + 状态压缩
        string s = to_string(int(pow(10, n))-1);
        
        unordered_map<int, int> memo;
        // 数位 DP 模板 上限:limit 下限:is_num
        auto f = [&] (this auto&& f, int state, int i, bool is_num, bool limit) -> int {
            if (i == n) return 1;   // 允许 0
            
            int mask  = state << 6 | i << 2 | is_num << 1 | limit;
            if (memo.count(mask)) return memo[mask];

            int res = 0;
            // 是否前导 0
            if (!is_num) res = f(state, i + 1, false, false); // limit = false
            int low = is_num?0 : 1;
            int up = limit? s[i] - '0': 9;
            for (int d=low; d<=up; ++d) {
                if (state >> d & 1) continue;
                res += f(state|1<<d, i+1, true, limit&&d==up);
            }            

            return memo[mask] = res;
        };

        return f(0, 0, false, true);
    }
};