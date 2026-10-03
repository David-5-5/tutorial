#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int superEggDrop(int k, int n) {
        // 自行解答，超时（TLE，time-limit exceeded)
        unordered_map<int, int> memo;

        auto dfs = [&] (this auto&& dfs, int i, int j) -> int {

            if (i == 1 || j <= 1) return j;

            int mask = i << 16 | j;
            if (memo.count(mask)) return memo[mask];

            int res = INT_MAX / 2;
            // 暴力
            for (int x=j; x>=1; x--) {  // O(k*n^2) 超时
                res = min(res, max(dfs(i-1, x-1), dfs(i, j-x)));
            }
            return memo[mask] = res + 1;
        };

        return dfs(k, n);
    }

    int superEggDrop2(int k, int n) {
        unordered_map<int, int> memo;

        auto dfs = [&] (this auto&& dfs, int i, int j) -> int {

            if (i == 1 || j <= 1) return j;

            int mask = i << 16 | j;
            if (memo.count(mask)) return memo[mask];

            int res = INT_MAX / 2;
            // Brute TLE
            // for (int x=1; x<=j; x++) {
            //     res = min(res, max(dfs(i-1, x-1), dfs(i, j-x)));
            // }
            // Optimize with binary search, 
            // f(x) = dfs(i-1, x-1) monotonic increasing , 
            // g(x) = dfs(i, j-x) monotonic decreasing
            // The achieves its minimum at x0, when f(x0) < g(x0) and f(x0+1) > g(x0+1)
            // the minimum value is min(max(f(x0), g(x0)), max(max(f(x0+1), g(x0+1))))
            int l = 0, r = j + 1;
            while (l + 1 < r) { 
                auto x = (l + r) / 2;
                auto t0 = dfs(i-1, x-1), t1 = dfs(i, j-x);
                auto s0 = dfs(i-1, x), s1 = dfs(i, j-x-1);
                if (t0 <= t1 && s0 >= s1) { // equals is must!!!
                    res = min(max(t0, t1), max(s0, s1)); break;
                } else if (t0 < t1 && s0 < s1) {
                    l = x;
                } else {
                    r = x;
                }
            }

            return memo[mask] = res + 1;
        };

        return dfs(k, n);
    }
};  

