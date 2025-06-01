#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.5 其他树形 DP
class Solution {    
public:
    long long pow(long long base, int exp, int modulo)
    {
        base %= modulo;
        long long res = 1;
        while (exp > 0)
        {
            if (exp & 1)
                res = res * base % modulo;
            base = base * base % modulo;
            exp >>= 1;
        }
        return res;
    }

    int waysToBuildRooms(vector<int>& prevRoom) {
        const int MOD = 1e9 + 7;
        int n = prevRoom.size();
        vector<vector<int>> g(n);

        long long fac = 1;
        for (int i=1; i<n; i++) {
            fac = fac * (i + 1) % MOD;
            g[prevRoom[i]].push_back(i);
        }
        
        long long mul = 1;
        auto dfs = [&] (this auto&& dfs, int u) -> int {
            int size = 1;
            for (auto& v : g[u]) {
                size += dfs(v);
            }

            mul = mul * size % MOD;
            return size;
        };
        dfs(0);
        return fac * pow(mul, MOD-2, MOD) % MOD;
        
    }
};