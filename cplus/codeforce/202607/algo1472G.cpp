#include <bits/stdc++.h>
using namespace std;

int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int t;
    cin >> t;
    for (int _=0; _<t; _++) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> g(n+1), rg(n+1); vector f(n+1, vector<int>(2, INT_MAX));

        for (int i=0; i<m; i++) {
            int u, v; cin >> u >> v;
            g[u].emplace_back(v); rg[v].emplace_back(u);
        }

        f[1][0] = 0, f[1][1] == 0;

        queue<int> forward; forward.push(1);
        while (!forward.empty()) {
            auto u = forward.front(); forward.pop();
            for (auto v: g[u]) {
                if (f[v][0] > f[u][0] + 1) {
                    f[v][0] = f[u][0] + 1;
                    forward.push(v);
                } else {
                    f[u][1] = min(f[u][1], f[v][0]);
                }
            }
        }

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> reverse;
        
        for (int i=1; i<=n; i++) {
            if (f[i][1] < INT_MAX) reverse.emplace(f[i][1], i);
        }

        while (!reverse.empty()) {
            auto [d, u] = reverse.top(); reverse.pop();
            if (d > f[u][1]) continue;
            for (auto v: rg[u]) {
                if (f[v][0] < f[u][0] && f[v][1] > d) {
                    f[v][1] = d;
                    reverse.emplace(d, v);
                }
            }
        }
        
        for (int i=1; i<=n; i++) {
            cout << min(f[i][0], f[i][1]) << " \n"[i==n];
        }
    }


    return 0;
}

