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
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();

        UnionFind uf(n);
        for (int i=1; i<n; i++) for (int j=0; j<i; ++j) {
            if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
                uf.merge(i, j);
        }
        return n - uf.cc;
    }
};