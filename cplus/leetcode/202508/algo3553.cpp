#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.8 最近公共祖先（LCA）、倍增算法
class Solution {
    // BEGIN 树上倍增 模板 - 全局变量 pa depth 带权重
    vector<int> depth;
    vector<long long> dis; // 如果是无权树（边权为 1），dis 可以去掉，用 depth 代替
    vector<vector<int>> pa;
    // END 树上倍增 模板 - 全局变量 pa depth    

public:
    // BEGIN 树上倍增 模板 - 接口方法 get_lca
    int get_kth_ancestor(int node, int k) {
        for (; k; k &= k - 1) {
            node = pa[node][countr_zero((unsigned) k)];
        }
        return node;
    }

    // 返回 x 和 y 的最近公共祖先（节点编号从 0 开始）
    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) {
            swap(x, y);
        }
        y = get_kth_ancestor(y, depth[y] - depth[x]); // 使 y 和 x 在同一深度
        if (y == x) {
            return x;
        }
        for (int i = pa[x].size() - 1; i >= 0; i--) {
            int px = pa[x][i], py = pa[y][i];
            if (px != py) {
                x = px;
                y = py; // 同时往上跳 2^i 步
            }
        }
        return pa[x][0];
    }

    // 返回 x 到 y 的距离（最短路长度）
    long long get_dis(int x, int y) {
        return dis[x] + dis[y] - dis[get_lca(x, y)] * 2;
    }
    // END 树上倍增 模板 - 接口方法 get_lca

    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        vector<vector<pair<int, int>>> g(n);
        for (auto& e : edges) {
            int x = e[0], y = e[1], w = e[2];
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }

        // BEGIN 树上倍增 模板 - 计算 pa depth
        int m = bit_width((unsigned) n); // n 的二进制长度
        depth.resize(n);
        dis.resize(n);
        pa.resize(n, vector<int>(m, -1));

        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            pa[x][0] = fa;
            for (auto& [y, w] : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dis[y] = dis[x] + w;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                if (int p = pa[x][i]; p != -1) {
                    pa[x][i + 1] = pa[p][i];
                }
            }
        }
        // END 树上倍增 模板 - 计算 pa depth
        vector<int> ans;
        for (auto & q :queries) {
            auto s1 = q[0], s2 = q[1], dest = q[2];

            // 点 s1, s2, dest 存在为祖先节点的情况，情况比较复杂
            // 简单的做法 两两计算距离然后取半
            ans.push_back((get_dis(s1, s2) + get_dis(s1, dest) + get_dis(s2, dest))/2);
        }
        return ans;
    }
};