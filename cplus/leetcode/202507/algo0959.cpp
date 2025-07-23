#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.2  并查集 - 进阶
class UnionFind {
    vector<int> fa;
public:
    int cc;         // 连通块个数
    UnionFind(int n): fa(n), cc(n) {
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
            fa[x] = y; cc--;
        }
    }
};

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        UnionFind uf(4 * n * n);     // 每个格子有四个方向，所以需要 4 * n * n 的空间
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                char c = grid[i][j];
                int base = 4 * (i * n + j);
                if (c == '/') {
                    uf.merge(base, base + 1);
                    uf.merge(base + 2, base + 3);
                } else if (c == '\\') {   
                    uf.merge(base, base + 3);
                    uf.merge(base + 1, base + 2);
                } else {              // ||
                    uf.merge(base, base + 1);
                    uf.merge(base + 1, base + 2);
                    uf.merge(base + 2, base + 3);
                }
                if (i > 0) {          // 向上合并
                    uf.merge(base+1, base - 4 * n + 3);
                }
                if (j > 0) {          // 向左合并
                    uf.merge(base, base - 4 + 2);
                }
            }
        }
        return uf.cc;
    }
};
