#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 13. 图 DP
class Solution {
public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        // 参考题解 畏难了，这题应该会的，动态规划暴力就可以
        if (n <= k) return -1;      // 剪枝
        vector<vector<pair<int, int>>> g(n);
        for (auto e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);   // 有向图
        }

        int ans = -1;

        unordered_map<int, bool> visited;
        auto dfs = [&](this auto&& dfs, int u, int l, int s) -> void {
            if (l == k) ans = max(ans, s);
            int mask = u << 19 | l << 10  | s;
            
            if (visited.count(mask)) return;
            for (auto& [v, w]: g[u]) {
                if (w + s < t) dfs(v, l+1, w+s);
            }
            visited[mask] = true;
        };

        for (int u=0; u<n; ++u) dfs(u, 0, 0);

        return ans;
    }

    int maxWeight2(int n, vector<vector<int>>& edges, int k, int t) {
        // 拓扑序 DP 针对 DAG
        if (n <= k) return -1;
        vector<vector<pair<int, int>>> g(n);
        vector<int> deg(n);
        for (auto e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);   // 有向图
            deg[e[1]] ++;
        }
        vector f(n, vector<unordered_set<int>>(k+1));
        queue<int> q;
        for (int i=0; i<n; ++i) if (deg[i] == 0) q.push(i);

        int ans = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            f[u][0].insert(0);     // x
            for (auto s : f[u][k]) {
                ans = max(ans, s);
            }

            for (auto& [v, w]: g[u]) {
                for (int i=0; i<k; ++i) { 
                    for (auto s: f[u][i]) {
                        if (s + w < t)
                            f[v][i+1].insert(s + w);
                    }
                }

                if (--deg[v] == 0) {
                    q.push(v);
                }
            }
            
        }
        return ans;
    }

    int maxWeight3(int n, vector<vector<int>>& edges, int k, int t) {
        // 拓扑序 DP 针对 DAG
        if (n <= k) return -1;
        vector<vector<pair<int, int>>> g(n);
        vector<int> deg(n);
        for (auto e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);   // 有向图
            deg[e[1]] ++;
        }

        // 使用 bitset 代替 unordered_set
        vector f(n, vector<bitset<600>>(k+1));
        queue<int> q;
        for (int i=0; i<n; ++i) if (deg[i] == 0) q.push(i);

        int ans = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            f[u][0].set(0);     // x
            for (int s = t-1; s>=0; --s) {
                if (f[u][k].test(s)) {
                    ans = max(ans, s);
                    break;
                }
            }

            for (auto& [v, w]: g[u]) {
                for (int i=0; i<k && !f[u][i].none(); ++i) 
                    f[v][i+1] |= f[u][i] << w;

                if (--deg[v] == 0) {
                    q.push(v);
                }
            }
        }
        return ans;
    }


};