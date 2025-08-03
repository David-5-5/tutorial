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

class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // 参考题解 数状数组 + 差分
        FenwickTree<int> ft(n);
        // memset(clock_in, n, 0); memset(clock_out, n, 0);
        unordered_map<long, int> weighs;
        vector<vector<pair<int, int>>> g(n+1, vector<pair<int, int>>());
        for (auto q:edges) {
            auto u = q[0], v = q[1], w = q[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
            weighs[(long)min(u,v)*n+max(u,v)] = w;
        }

        vector<int> clock_in(n+1), clock_out(n+1);
        int clock = 0;
        auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
            clock_in[u] = ++clock;
            for (auto [v, w]: g[u]) {
                if (v == fa) continue;
                dfs(v, u);
                ft.update(clock_in[v], w);
                ft.update(clock_out[v]+1, -w);
            }
            clock_out[u] = clock;
        };
        dfs(1, 0);

        vector<int> ans;
        for (auto q: queries) {
            if (q[0] == 2){
                ans.push_back(ft.pre(clock_in[q[1]]));
            } else {
                auto u = q[1], v = q[2], w = q[3];
                auto delta = w - weighs[(long)min(u,v)*n+max(u,v)];
                if (clock_in[u] < clock_in[v]) { // v 是子节点
                    ft.update(clock_in[v], delta);
                    ft.update(clock_out[v]+1, -delta);
                } else { //u 是子节点
                    ft.update(clock_in[u], delta);
                    ft.update(clock_out[u]+1, -delta);
                }
                weighs[(long)min(u,v)*n+max(u,v)] = w;
            }
        }
        return ans;

    }
};