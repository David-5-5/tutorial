#include <bits/stdc++.h>
using namespace std;

// 图论算法 四、最小生成树

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
    int minCostConnectPoints(vector<vector<int>>& points) {
        // 自行解答， 未复习最小生成算法，使用 UnionFind 模板结合优先队列，
        // 寻找代价最小的 n - 1 条边。
        int n = points.size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

        for (int i=1; i<n; i++) for (int j=0; j<i; j++) {
            int cost = abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]);
            pq.emplace(cost, i, j);
        }

        UnionFind uf(n);

        int ans = 0, edges = 0;
        while (edges < n-1) {
            auto [c, x, y] = pq.top(); pq.pop();
            if (uf.is_same(x, y)) continue; // x y 已经在同一连通块中
            uf.merge(x, y);         // 每使用一条边，连接两个连通块
            ans += c; edges ++;
        }
        return ans;
    }
};