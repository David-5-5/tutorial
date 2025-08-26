#include <bits/stdc++.h>
using namespace std;

// quick pow 模板
const int MOD = 1e9 + 7;
long long pow(long long base, int exp, int modulo)
{
    base %= modulo;
    long long res = 1;
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base % modulo;
        base = base * base % modulo;
        exp >>= 1;
    }
    return res;
}

// 一般树 - 3.8 最近公共祖先（LCA）、倍增算法
class Solution {
    // BEGIN 树上倍增 模板 - 全局变量 pa depth
    vector<int> depth;
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
    // END 树上倍增 模板 - 接口方法 get_lca

    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int x = e[0]-1, y = e[1]-1;
            g[x].emplace_back(y);
            g[y].emplace_back(x);
        }

        // BEGIN 树上倍增 模板 - 计算 pa depth
        int m = bit_width((unsigned) n); // n 的二进制长度
        depth.resize(n);
        pa.resize(n, vector<int>(m, -1));

        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            pa[x][0] = fa;
            for (auto& y : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
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
        for (auto & q: queries) {
            auto x = q[0]-1, y = q[1]-1;
            auto lca = get_lca(x, y);
            auto dis = depth[x] + depth[y] - 2 * depth[lca];
            if (dis == 0) ans.push_back(0);
            else ans.push_back(pow(2, dis-1, MOD));
        }
        return ans;
    }

};