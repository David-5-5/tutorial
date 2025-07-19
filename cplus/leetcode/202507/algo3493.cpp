#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.1 并查集 - 基础
class UnionFind {                   // 并查集模板
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
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        // 参考题解，并查集
        int n = properties.size();
        vector<unordered_set<int>> sets(n);
        for (int i=0; i<n; i++) {
            sets[i] = unordered_set(properties[i].begin(), properties[i].end());
        }

        UnionFind uf(n);
        for (int i=0; i<n; ++i) for (int j=0; j<i; ++j) {
            int cnt = 0;
            for (int x:sets[j]){
                if (sets[i].contains(x)) cnt ++;
            }
            if (cnt >= k) uf.merge(i, j);
        }
        return uf.cc;
    }
};