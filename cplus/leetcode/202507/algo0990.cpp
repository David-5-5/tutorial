#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.1 并查集 - 基础
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
            fa[x] = y;
        }
    }

    bool is_same(int x, int y) {
        return find(x) == find(y);
    }
};


class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        auto uf = UnionFind(26);
        for (auto& eq:equations) {
            if (eq[1] == '=') if (eq[0]!=eq[3]) uf.merge(eq[0]-'a', eq[3]-'a');
        }
        for (auto& eq:equations) {
            if (eq[1] == '!' && uf.is_same(eq[0]-'a', eq[3]-'a')) return false; 
        }
        return true;
    }
};