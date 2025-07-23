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
    int numSimilarGroups(vector<string>& strs) {

        auto is_similiar = [&](int i, int j) -> bool {
            int first = -1, second = -1;
            for (int k=0; k<strs[i].length(); ++k) {
                if (strs[i][k] != strs[j][k]) {
                    if (first == -1) first = k;
                    else if (second == -1) second = k;
                    else return false;
                }
            }
            if (first == -1 && second == -1) return true;   // 性能好
            else if (second == -1) return false;
            return strs[i][first] == strs[j][second] && strs[i][second] == strs[j][first];
        };

        int n = strs.size();

        UnionFind uf(n);
        for (int i=1; i<n; i++) for (int j=0; j<i; ++j) {
            if (is_similiar(i, j))
                uf.merge(i, j);
        }
        return uf.cc;        
    }
};