#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int superEggDrop(int k, int n) {
        unordered_map<int, int> memo;

        auto dfs = [&] (this auto&& dfs, int i, int j) -> int {

            if (i == 1 || j <= 1) return j;

            int mask = i << 16 | j;
            if (memo.count(mask)) return memo[mask];

            int res = INT_MAX / 2;
            // 暴力
            // for (int x=j>50?j/2:j; x>=1; x--) {
            for (int x=j; x>=1; x--) {  // O(k*n^2) 超时
                res = min(res, max(dfs(i-1, x-1), dfs(i, j-x)));
            }
            return memo[mask] = res + 1;
        };

        return dfs(k, n);
    }
};