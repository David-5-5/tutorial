#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大 倒序贪心
class Solution {
public:
    string smallestNumber(string num, long long t) {
        // 参考题解 数位 DP
        vector<int> primes = {2, 3, 5 , 7}; auto tmp = t;
        int cnt = 0;

        for (auto &p : primes) {
            while (tmp % p == 0) {
                tmp /= p; cnt ++;
            }
        }
        if (tmp > 1) return "-1";

        cnt = max(1, cnt - (int)num.length() + 1);

        string s(cnt, '0');
        s.insert(s.end(), num.begin(), num.end());

        int n = s.length();
        string ans(n, '0');

        unordered_map<long long, bool> memo;
        auto dfs = [&](this auto&& dfs, int i, long long t, bool isLimit) -> bool {
            if (i == n) return t == 1;
            long long mask = (long long) i << 50 | (long long)isLimit << 48 | t;
            if (memo.count(mask)) return memo[mask];

            if (isLimit && i < cnt && dfs(i+1, t, isLimit)) return memo[mask] = true;

            int low = isLimit?s[i] - '0': 0;
            for (int d=max(low, 1); d<10; d++) {
                ans[i] = d + '0';
                if (dfs(i+1, t/gcd(t,d), isLimit && d == low)) return memo[mask] = true;
            }
            ;
            return memo[mask] = false;
        };

        dfs(0, t, true);
        int inx = 0; while (ans[inx] == '0') inx ++;
        return ans.substr(inx);

    }    
};
