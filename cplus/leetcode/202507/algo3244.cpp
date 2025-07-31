#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.5 并查集 - 区间并查集
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


class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        // 参考题解
        int ans = n - 1;
        UnionFind uf(n-1);
        vector<int> ret(queries.size(), ans);

        for (int i =0; i<queries.size(); ++i) {
            auto &q = queries[i];
            int u = q[0], v = q[1]-1;

            // 并查集，连接到靠右的节点
            if (uf.find(u) != uf.find(v)) {
                // 合并技巧:合并到最右节点
                // for (int x=u+1; x<=v && uf.find(u)!=uf.find(v); x=max(x+1,x+1<n-1?uf.find(x+1):x+1)) {
                //     uf.merge(u, x);
                // }

                // 这种写法更清晰，
                auto x = uf.find(u+1);
                while (uf.find(u)!=uf.find(v)) {
                    uf.merge(u, x);
                    // 性能技巧，不能使用 x=u+1, x++; 性能超时，需要uf.find找最右边的点
                    x = x+1<n-1?uf.find(x+1):x+1;   // 避免越界
                }
            }
            ret[i] = uf.cc;
        }

        return ret;
    }
};