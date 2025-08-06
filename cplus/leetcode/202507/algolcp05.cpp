#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.1 树状数组和线段树 - 树状数组
template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    // 使用下标 1 到 n
    FenwickTree(int n) : tree(n + 1) {}
    // a[i] 增加 val, 1 <= i <= n
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }
    // 求前缀和 a[1] + ... + a[i] 1 <= i <= n
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) { // i-= i&-i
            res += tree[i];
        }
        return res;
    }
    // 求区间和 a[l] + ... + a[r], 1 <= l <= r <= n
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};

// 双树状数组 模板 区间更新
void range_update(FenwickTree<long>& ft1, FenwickTree<long>& ft2, int l, int r, int delta) {
    // 更新 ft1 (d[i])
    ft1.update(l, delta);
    ft1.update(r + 1, -delta);
    // 更新 ft2 (i*d[i])
    ft2.update(l, l * delta);
    ft2.update(r + 1, -(r + 1) * delta);
}

long range_query(FenwickTree<long>& ft1, FenwickTree<long>& ft2, int x) {
    return (x + 1) * ft1.pre(x) - ft2.pre(x);
}

// 双树状数组 模板 区间查询
long interval_query(FenwickTree<long>& ft1, FenwickTree<long>& ft2, int l, int r) {
    return range_query(ft1, ft2, r) - range_query(ft1, ft2, l - 1);
}

class Solution {
public:
    vector<int> bonus(int n, vector<vector<int>>& leadership, vector<vector<int>>& operations) {
        // 双树状数组，完成区间更新以及区间查询
        const int mod = 1e9 + 7;
        FenwickTree<long> ft1(n);
        FenwickTree<long> ft2(n);
        vector<vector<int>> g(n+1, vector<int>());
        for (auto q:leadership) {
            auto u = q[0], v = q[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        vector<int> clock_in(n+1), clock_out(n+1);
        int clock = 0;
        auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
            clock_in[u] = ++clock;
            for (auto v: g[u]) {
                if (v == fa) continue;
                dfs(v, u);
            }
            clock_out[u] = clock;
        };
        dfs(1, 0);

        vector<int> ans;
        for (auto q: operations) {
            if (q[0] == 3){
                ans.push_back(interval_query(ft1, ft2, clock_in[q[1]], clock_out[q[1]])%mod);
            } else if (q[0] == 2) {
                auto u = q[1], w = q[2];              
                range_update(ft1, ft2, clock_in[u], clock_out[u], w);
            } else {
                auto u = q[1], w = q[2];
                range_update(ft1, ft2, clock_in[u], clock_in[u], w);
            }
        }
        return ans;

    }
};