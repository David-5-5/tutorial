#include <bits/stdc++.h>
using namespace std;

class UnionFind {
    vector<int> fa;
public:
    int cc;
    UnionFind(int n): fa(n), cc(n){
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

// LCR
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // 自行解答 并查集
        int n = graph.size(); UnionFind uf(n);
        for (int u=0; u<n; ++u) {
            for (int i=1; i<graph[u].size(); ++i) 
                uf.merge(graph[u][0], graph[u][i]);
            
                for (auto & v: graph[u]) 
                if (uf.find(v) == uf.find(u)) return false;
        }

        return true;
    }
};