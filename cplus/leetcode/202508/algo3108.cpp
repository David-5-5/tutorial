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
};