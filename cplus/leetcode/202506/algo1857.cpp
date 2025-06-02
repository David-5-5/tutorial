#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 13. 图 DP
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        // 自行解答
        int n = colors.size();
        vector<vector<int>> g(n);
        vector<int> deg(n);
        for (auto e : edges) {
            g[e[0]].push_back(e[1]);   // 有向图
            deg[e[1]] ++;
        }

        vector f(n, vector<int>(26));
        queue<int> q;
        vector<bool> visited(n, false);
        int ans = -1;
        for (int i=0; i<n; ++i)
            if (deg[i] == 0) {
                q.push(i), f[i][colors[i]-'a']=1;
                ans = max(f[i][colors[i]-'a'], ans);
            }

        while (!q.empty()) {    // toplogy sort
            int u = q.front();
            q.pop();
            visited[u] = true;
            
            for (auto v : g[u]) {
                for (int i=0; i<26; ++i){
                    f[v][i] = max(f[v][i], f[u][i]+ (colors[v]-'a'==i?1:0));
                    ans = max(ans, f[v][i]);
                }
                if (--deg[v] == 0) q.push(v); 
            }
        }

        // 若无环，每个节点都访问一次， 所有节点 visited = true
        if (!all_of(visited.begin(), visited.end(), [](bool vis){return vis;})){
            return -1;
        }
        return ans; 
    }
};