#include <bits/stdc++.h>
using namespace std;

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

// 常用数据结构 - 专题 - 离线算法
class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        // 求连通图 用并查集
        UnionFind uf(n);
        sort(edgeList.begin(), edgeList.end(), [](const auto& a, const auto& b){
            return a[2] < b[2]; 
        });
        int l = 0, t = edgeList.size(), m = queries.size();
        vector<bool> ans(m);
        int idx[m];
        iota(idx, idx+m, 0);
        sort(idx, idx + m, [&](int i, int j) {
            return queries[i][2] < queries[j][2];
        });

        for (int i : idx) {
            while (l < t && edgeList[l][2] < queries[i][2]) {
                uf.merge(edgeList[l][0], edgeList[l][1]);
                l ++;
            }
            ans[i] = uf.find(queries[i][0]) == uf.find(queries[i][1]);
        }
        return ans;     
    }
};