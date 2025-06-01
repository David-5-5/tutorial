#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.4 换根 DP
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // 自行解答， 换根 DP
        vector<vector<int>> g(n);
        for (auto& e: edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v), g[v].push_back(u);
        }

        vector<vector<pair<int, int>>> heights(n, vector<pair<int,int>>(2, {0, -1}));
        
        // auto dfs = [&](this auto&& dfs, int u, int fa) -> int {
        function<int(int, int)> dfs = [&](int u, int fa) -> int {
            for (auto& v : g[u]) {
                if (v == fa) continue;
                int h = 1 + dfs(v, u);
                if (h > heights[u][0].first) {
                    heights[u][1] = heights[u][0];
                    heights[u][0] = {h, v};
                } else if (h > heights[u][1].first) {
                    heights[u][1] = {h, v};
                }
            }
            return heights[u][0].first;
        };
    
        dfs(0, -1);

        int mn_height = INT_MAX;
        vector<int> ans;

        // auto reboot = [&](this auto&& dfs, int u, int fa) {
        function<void(int, int)> reboot =  [&](int u, int fa) {
            if (heights[u][0].first < mn_height) {
                ans = {u};
                mn_height = heights[u][0].first;
            } else if (heights[u][0].first == mn_height) ans.push_back(u);

            for (auto& v : g[u]) {
                if (v == fa) continue;
                int h = 1 + (v != heights[u][0].second?heights[u][0].first:heights[u][1].first);
                if (h > heights[v][0].first) {
                    heights[v][1] = heights[v][0];
                    heights[v][0] = {h, u};
                } else if (h > heights[v][1].first) {
                    heights[v][1] = {h, u};
                }                
                reboot(v, u);
            }

        };
        reboot(0, -1);
        return ans;
    }

};

int main() {
    vector<vector<int>> edges = {{1,0},{1,2},{1,3}};
    vector ans = Solution().findMinHeightTrees(4, edges);
    // for (auto v:ans) cout << v << ", ";
}