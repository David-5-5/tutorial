#include <bits/stdc++.h>
using namespace std;


int main() {
    // 极致输入加速（比ios::sync_with_stdio更快）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::badbit | ios::failbit);

    int n, m; cin >> n >> m;
    vector<int> a(n), colors(n), ts_in(n), ts_out(n);
    for (int i=0; i<n; i++) {
        cin >> colors[i];
    }
    vector<vector<int>> g(n);
    for (int _=0; _<n-1; _++) {
        int u, v;
        cin >> u >> v;
        g[u-1].emplace_back(v-1);
        g[v-1].emplace_back(u-1);
    }

    int ts = -1;
    auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
        ts ++;
        ts_in[u] = ts;
        for (auto & v : g[u]) {
            if (v == fa) continue;
            dfs(v, u);
        }
        ts_out[u] = ts;
    };
    dfs(0, -1);

    vector<long long> tree(4 * n);
    vector<int> tp(4 * n);     // 支持懒标记

    // 下推懒标记
    auto pushdown = [&] (int s, int t, int p) -> void{
        if (s == t) return;  // 叶子节点无需下推
        // 更新左子树
        tree[p * 2 + 1] = 1LL << tp[p]; tp[p * 2 + 1] = tp[p];
        // 更新右子树
        tree[p * 2 + 2] = 1LL << tp[p]; tp[p * 2 + 2] = tp[p];
        // 清空当前节点懒标记
        tp[p] = 0;
    };

    auto update = [&](this auto&& update, int l, int r, int color, int s, int t, int p) -> void{
        if (l <= s && t <= r) {
            // 当前区间完全在更新范围内
            tree[p] = 1LL << color;      // 区间 + val
            if (s != t) tp[p] = color; // 非叶子节点才需要标记
            return;
        }
        // 下推懒标记
        if (tp[p] != 0) pushdown(s, t, p);

        int m = s + ((t - s) >> 1);
        // 递归更新左子树
        if (l <= m)  update(l, r, color, s, m, p * 2 + 1);
        // 递归更新右子树
        if (r > m) update(l, r, color, m + 1, t, p * 2 + 2);
        // 更新当前节点值
        tree[p] = tree[p * 2 + 1] | tree[p * 2 + 2];
    };

    // 区间更新：[l, r] 区间增加 value
    auto query = [&](this auto&& query, int l, int r, int s, int t, int p) -> long long {
        // 下推懒标记
        if (l <= s && t <= r) {
            // 当前区间完全在更新范围内
            return tree[p];
        }
        if (tp[p] != 0) pushdown(s, t, p);

        int m = s + ((t - s) >> 1);
        if (r <= m)
            return query(l, r, s, m, p * 2 + 1);
        else if (l > m)
            return query(l, r, m + 1, t, p * 2 + 2);
        else 
            return query(l, r, s, m, p * 2 + 1) | query(l, r, m + 1, t, p * 2 + 2);
    };
    // 参考 oi-wiki 线段树模板 - 区间更新 最大值

    for (int i=0; i<n; i++) update(ts_in[i], ts_in[i], colors[i], 0, n-1, 0);

    for (int _=0; _<m; _++) {
        int type; cin >> type;
        if (type == 1) {
            int u, c; cin >> u >> c;
            update(ts_in[u-1], ts_out[u-1], c, 0, n-1, 0);
        } else {
            int u; cin >> u;
            long long colors = query(ts_in[u-1], ts_out[u-1], 0, n-1, 0);
            cout << popcount(static_cast<unsigned long long>(colors)) << endl;
        }
    }

    return 0;
}

