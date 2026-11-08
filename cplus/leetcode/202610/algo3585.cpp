#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<int> depth;
    vector<long long> dis; // 如果是无权树（边权为 1），dis 可以去掉，用 depth 代替
    vector<vector<int>> pa;
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

    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
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
            for (int i = 1; i < m; i++) {
                pa[x][i] = pa[x][i-1] == -1 ? -1 : pa[pa[x][i-1]][i-1];
            }            
            for (auto& [y, w] : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dis[y] = dis[x] + w;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);
        

        auto find = [&](this auto && find, int u, long long d, bool ge) -> int {
            
            int i = 0;

            while (pa[u][i]!=-1 && (dis[u] - dis[pa[u][i]]) * 2 < d) i++;
            
            if (pa[u][i]!=-1 && (dis[u] - dis[pa[u][i]]) * 2 == d) return pa[u][i];
            if (i == 0) {
                return ge ? pa[u][0]: u;
            };
            auto v = pa[u][i-1];
            return find(v, d-2*(dis[u] - dis[v]), ge);

        };

        vector<int> ans;
        for (auto &q: queries) {
            auto u = q[0], v = q[1];
            // cout << u << ", " << v << endl;
            auto par = get_lca(u, v);
            // cout << par << endl;
            if (par != u && par != v) {
                if (dis[u] - dis[par] == dis[v] - dis[par]) ans.emplace_back(par);
                else {
                    auto uv = get_dis(u, v); // ceil
                    if (dis[u] - dis[par] > dis[v] - dis[par])
                        ans.emplace_back(find(u, uv, true)); // great && equal than half
                    else ans.emplace_back(find(v, uv, false)); // less && equal than half
                }
            } else {
                auto uv = get_dis(u, v);
                // cout << uv << endl;
                par == u ? ans.emplace_back(find(v, uv, false)): ans.emplace_back(find(u, uv, true));
            }
        }

        return ans;
    }
};

int main() {
    vector<vector<int>> edges = {{0,1,7},{1,2,5}};
    vector<vector<int>> queries = {{0,2}}; 
    Solution().findMedian(3, edges, queries);
}