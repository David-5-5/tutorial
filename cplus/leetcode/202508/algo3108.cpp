#include <bits/stdc++.h>
using namespace std;


class UnionFind {
    vector<int> fa;
    vector<int> _and;
public:
    UnionFind(int n): fa(n), _and(n, -1) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to, int w) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y; _and[y] &= w & _and[x];
        } else _and[y] &= w;
    }

    int get_weight(int x) {
        return _and[find(x)];
    }
};

// 位运算 - 与或（AND/OR）的性质
// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS） 2026/1/19
class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        // 并查集 - 自行解答
        UnionFind uf(n); 
        for (auto& e : edges) {
            auto u = e[0], v = e[1], w = e[2];
            uf.merge(u, v, w);
        }

        vector<int> ans;
        for (auto& q: query) {
            auto x = uf.find(q[0]), y = uf.find(q[1]);
            if (x == y) ans.push_back(uf.get_weight(x));
            else ans.push_back(-1);
        }
        return ans;
    }

    vector<int> minimumCost2(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        // dfs
        vector<vector<pair<int, int>>> g(n);
        for (auto & e: edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            g[e[1]].emplace_back(e[0], e[2]); 
        }
        vector<int> comp_and;
        vector<int> ids(n, -1);

        for (int i=0; i<n; i++) {
            if (ids[i] >= 0) continue;
            auto dfs = [&] (this auto&& dfs, int u) -> int {
                ids[u] = comp_and.size();
                int res = -1;
                for (auto& [v, w] : g[u]) {
                    // 保证边的遍历，相对于并查集，容易出错，并查集是仅遍历每条边
                    // 而 DFS 是从点去遍历每条边
                    res &= w;       // this statement must be there!!!
                    if (ids[v] >= 0) continue;
                    res &= dfs(v);
                }
                return res;
            };
            comp_and.push_back(dfs(i));
        }

        vector<int> ans;
        for (auto& q: query) {
            if (ids[q[0]] != ids[q[1]]) {
                ans.push_back(-1);
            }else ans.push_back(comp_and[ids[q[0]]]);
        }
        return ans;   
    }
};