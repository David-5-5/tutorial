#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        // 自行解答 - dfs 遍历
        int n = nums.size();
        vector<vector<int>> g(n); vector<bool> vis(n);
        for (auto& e : swaps)  {
            g[e[0]].emplace_back(e[1]); g[e[1]].emplace_back(e[0]);
        }

        long long ans = 0;

        for (int i=0; i<n; i++) {
            vector<int> s_set; int odd = 0;
            auto dfs = [&] (this auto&& dfs, int u) -> void {
                if (vis[u]) return;
                vis[u] = true;
                s_set.push_back(nums[u]);
                nums[u] = 0; if (u % 2) odd ++;                
                for (auto & v: g[u]) {
                    dfs(v);
                }
            };
            dfs(i);
            sort(s_set.begin(), s_set.end());
            for (int j=0; j<s_set.size(); ++j) {
                if (j < odd) ans -= s_set[j];
                else ans += s_set[j];
            }
        }

        for (int i=0; i<n; ++i) {
            if (i % 2) ans -= nums[i];
            else ans += nums[i];
        }
        return ans;
    }

    long long maxAlternatingSum2(vector<int>& nums, vector<vector<int>>& swaps) {
        // 自行解答 - 两种 vis 遍历方法 设置 vis[u] vs vis[v]
        int n = nums.size();
        vector<vector<int>> g(n); vector<bool> vis(n);
        for (auto& e : swaps)  {
            g[e[0]].emplace_back(e[1]); g[e[1]].emplace_back(e[0]);
        }

        long long ans = 0;

        for (int i=0; i<n; i++) {
            vector<int> s_set; int odd = 0;
            auto dfs = [&] (this auto&& dfs, int u) -> void {
         
                for (auto & v: g[u]) {
                    if (vis[v]) continue;
                    vis[v] = true;
                    s_set.push_back(nums[v]);
                    nums[v] = 0; if (v % 2) odd ++;       
                    dfs(v);
                }
            };
            dfs(i);
            sort(s_set.begin(), s_set.end());
            for (int j=0; j<s_set.size(); ++j) {
                if (j < odd) ans -= s_set[j];
                else ans += s_set[j];
            }
        }

        for (int i=0; i<n; ++i) {
            if (i % 2) ans -= nums[i];
            else ans += nums[i];
        }
        return ans;        
    }    
};