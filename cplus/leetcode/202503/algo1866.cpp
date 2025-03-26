#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int rearrangeSticks(int n, int k) {
        // 暴力，时间复杂度 O(n!*k)，需要优化到 O(nk)/O(nklogn)

        const int mod = 1e9 + 7;
        unordered_set<int> visited;

        auto dfs = [&](this auto&& dfs, int l, int m) -> int {
            if (l<0) return 0;
            if (visited.size() == n) return l==0?1:0;

            int res = 0;
            for (int i=1; i<=n; i++) {
                if (visited.count(i)) continue;
                visited.emplace(i);
                res += dfs(l-(i>m?1:0), max(i, m));
                visited.erase(i);
            }
            return res % mod;
        };

        return dfs(k, 0);   
        
    }
};