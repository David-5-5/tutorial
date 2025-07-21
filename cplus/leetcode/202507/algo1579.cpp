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
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        // 自行解答，分两次遍历，第一次处理公共边，第二次分别处理1和2的边
        UnionFind uf1(n), uf2(n);
        int ans = 0;
        for (auto &e : edges) {
            int u = e[1]-1, v = e[2] -1 ;
            if (e[0] == 3) {
                if (uf1.find(u) != uf1.find(v)) {
                    uf1.merge(u, v); uf2.merge(u, v);
                }else ans ++;
            }
        }

        for (auto &e : edges) {
            int u = e[1]-1, v = e[2] -1 ;
            if (e[0] == 2) {
                if (uf2.find(u) != uf2.find(v))
                    uf2.merge(u, v);
                else ans ++;                
            } else if (e[0] == 1) {
                if (uf1.find(u) != uf1.find(v)) 
                    uf1.merge(u, v);
                else ans ++;                  
            }
        }
        return (uf1.cc==1 && uf2.cc==1)?ans:-1 ;
    }
};