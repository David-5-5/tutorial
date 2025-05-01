#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 数位 DP
class Solution {
public:
    int countSpecialNumbers(int n) {
        // 复习 - 自行解答 同 357， 差异点在于 0 是否合法数据
        string s = to_string(n);
        int m = s.length();
        
        unordered_map<int, int> memo;
        // included 至少需要包含 2， 5， 6， 9 中的一个
        auto f = [&] (this auto&& f, int state, int i, bool is_num, bool limit) -> int {
            if (i == m) return is_num;  // 不允许 0
            
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