#include <bits/stdc++.h>
using namespace std;

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

// 图论算法 四、最小生成树
class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        // 自行解答 Kruskal 算法，找最大强度
        int cnt = 0, mn = 1e6; UnionFind uf(n);
        priority_queue<tuple<int, int, int>> pq;    // 大根堆
        for (auto & e: edges) {
            auto u = e[0], v = e[1], s = e[2], must = e[3];
            if (must) {
                mn = min(mn, s); cnt ++;
                if (!uf.is_same(u, v)) uf.merge(u, v);
                else return -1;
            } else {
                pq.emplace(s, u, v);
            }
        }
        vector<int> upgrades;
        while (cnt < n-1 && !pq.empty()) {
            auto [s, u, v] = pq.top(); pq.pop();
            if (!uf.is_same(u, v)) {
                cnt ++; uf.merge(u, v);
                if (s < mn) upgrades.emplace_back(s);
            }
        }
        if (cnt < n-1) return -1;
        sort(upgrades.begin(), upgrades.end());
        for (int i=0; i<k && i<upgrades.size(); i++) {
            if (upgrades[i]*2 < mn) mn = upgrades[i]*2;
        }

        return upgrades.size()>k?min(upgrades[k], mn):mn;
    }

  
};