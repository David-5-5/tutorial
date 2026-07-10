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
        int k;
        cin >> k;
        vector g(2*k, vector<pair<int, int>>());
        for (int i=0; i<2*k-1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            g[u-1].emplace_back(v-1, w);
            g[v-1].emplace_back(u-1, w);
        }
        long long good = 0, bad = 0;
        function<int(int, int)> dfs = [&](int u, int fa) -> int {
            int res = 0;
            for (auto [v, w]: g[u]) {
                if (v == fa) continue;
                auto v_cnt = dfs(v, u);
                good += 1LL * (v_cnt % 2) * w;
                bad += 1LL * w * min(v_cnt, 2*k - v_cnt);
                res += v_cnt;
            }
            return res + 1;
        };

        dfs(0, -1);
        cout << good << " " << bad << endl;
    }
}
