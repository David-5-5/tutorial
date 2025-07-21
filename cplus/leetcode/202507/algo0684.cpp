#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.2  并查集 - 进阶
class UnionFind {                   // 并查集模板
    vector<int> fa;
public:
    UnionFind(int n): fa(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[max(x,y)] = min(x,y);    // 大的连接小的
        }
    }

    bool is_same(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        UnionFind uf(edges.size()+1);
        for (auto& e: edges) {
            int u = e[0], v = e[1];
            if (uf.is_same(u, v)) return {u, v};
            else uf.merge(u, v);
        }
        return {};
    }
};