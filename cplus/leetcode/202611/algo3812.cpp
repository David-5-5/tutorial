#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start, string target) {
        vector<set<pair<int, int>>> g(n);
        for (int i=0; i<n-1; i++) {
            auto & u = edges[i][0], & v = edges[i][1];
            g[u].emplace(v, i);
            g[v].emplace(u, i);
        }

        queue<int> que;
        for (int u=0; u<n; u++) {
            if (g[u].size() == 1) que.push(u);
        }
        vector<int> ans;
        while (!que.empty()) {
            auto u = que.front(); que.pop();

            if (g[u].empty()) {
                if (start[u]!=target[u]) ans = {-1};
                continue;
            }
            auto v = g[u].begin()->first, e = g[u].begin()->second;
            if (start[u] != target[u]) {
                start[v] = (start[v] == '1')?'0':'1';
                ans.emplace_back(e);
            }
            // g[u].erase({v, e});
            g[v].erase({u, e});
            if (g[v].size() == 1) que.push(v);
        }
        sort(ans.begin(), ans.end());
        return ans;   
    }
};

int main() {
    vector<vector<int>> edges  = {{0,1},{1,2},{2,3},{3,4},{3,5},{1,6}};
    Solution().minimumFlips(7, edges, "0011000", "0010001");
}