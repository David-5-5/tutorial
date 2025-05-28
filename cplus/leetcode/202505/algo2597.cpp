#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 一维 DP
class Solution {
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        // 复习，动态规划 + 乘法原理 + 加法原理

        // 按 v%k 分组，不同组之间的差肯定不等于 k
        // 因此不同组之间子集的数目使用乘法原理，同一组内的子集的数目使用加法原理
        unordered_map<int, map<int, int>> group;
        for (auto& v: nums) {
            group[v%k][v] ++;
        }

        int ans = 1;
        for (auto& [_, cnt] : group) {
            int m = cnt.size();
            vector<pair<int, int>> g;
            transform(cnt.begin(), cnt.end(), back_inserter(g), [](const auto& val) {
                return pair<int, int>(val.first, val.second);
            });
            // vector<int> memo(m+1, -1);                  // using memo 12ms, without memo 3ms
            auto dfs = [&](this auto&& dfs, int i) {
                if (i == 0) return 1;
                // auto & res = memo[i];
                // if (res != -1) return res;
                int res = dfs(i-1);
                res += ((int)pow(2, g[i-1].second)-1) * ((i == 1 || g[i-1].first-g[i-2].first!=k) ? dfs(i-1) : dfs(i-2));
                return res;
            };
            
            ans *= dfs(m);
        }
        return ans-1;
    }


    int beautifulSubsets2(vector<int>& nums, int k) {
        // 复习，递归 -> 迭代
        unordered_map<int, map<int, int>> group;
        for (auto& v: nums) {
            group[v%k][v] ++;
        }

        int ans = 1;
        for (auto& [_, cnt] : group) {
            int m = cnt.size();
            vector<int> f(m+1);
            f[0] = 1;
            auto it = cnt.begin();
            for (int i=1; i<=m; i++, it++) {
                f[i] = f[i-1];
                f[i] += ((int)pow(2, it->second)-1) * ((it == cnt.begin() || it->first-prev(it)->first!=k)?f[i-1]:f[i-2]);
            };
            
            ans *= f[m];
        }
        return ans-1;
    }
};