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
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        UnionFind uf(26);
        for (int i=0; i<s1.length(); ++i) uf.merge(s1[i]-'a', s2[i]-'a');

        string ans = "";
        for (auto& ch:baseStr) ans += 'a' + uf.find(ch-'a');
        return ans;
    }
};