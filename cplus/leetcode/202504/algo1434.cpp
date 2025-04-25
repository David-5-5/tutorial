#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        // 自行解答，超时
        const int mod = 1e9 + 7;
        int n = hats.size();
        
        unordered_map<long, int> memo;
        auto dfs = [&](this auto&& dfs, long s) -> int {
            int i = __builtin_popcount(s);
            if (i == n) return 1;
            
            if (memo.count(s)) return memo[s];

            long res = 0;
            for (auto& v : hats[i]) {
                if ((s>>v & 1) == 0) {
                    res += dfs(s|(long)1<<v);
                }
            }
            return memo[s] = (res % mod);
        };

        return dfs(0);
    }

    int numberWays2(vector<vector<int>>& hats) {
        // 参考题意，自行解答
        // 帽子多，人少 变换为人戴帽子
        const int mod = 1e9 + 7;
        int n = hats.size(), mx = 0;
        vector<vector<int>> persons(40, vector<int>());
        for (int i=0; i<n; i++) {
            for (auto& v : hats[i]) {
                persons[v-1].push_back(i);
                mx = max(v, mx);
            }
        }
        
        unordered_map<int, int> memo;
        // 将 帽子戴 n 个人头上，s 第 i 个人是否戴帽子
        auto dfs = [&](this auto&& dfs, int i, int s) -> int {
            int j = __builtin_popcount(s);
            if (j == n) return 1;
            if (n-j > mx-i) return 0; // 剩下的帽子不够了
            
            int mask = i << 10 | s;
            if (memo.count(mask)) return memo[mask];

            long res = dfs(i+1, s);     // 不选
            for (auto& v : persons[i]) {
                if ((s>>v & 1) == 0) {
                    res += dfs(i+1, s|1<<v);
                }
            }
            return memo[mask] = (res % mod);
        };

        return dfs(0, 0);
    }    
};