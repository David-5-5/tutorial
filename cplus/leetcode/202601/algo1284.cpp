#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.3 图论建模 + BFS 最短路
class Solution {
public:
    int minFlips(vector<vector<int>>& mat) {
        // 自行解答
        int m = mat.size(), n = mat[0].size();
        vector<int> q; set<int> vis;

        int start = 0, step = 0;
        for (int r=0; r<m; r++) for (int c=0; c<n; c++) {
            start |= mat[r][c] << (r * n + c);
        }
        q.emplace_back(start); vis.insert(start);
        while (!q.empty()) {
            vector<int> nxt;
            for (auto& u: q) {
                if (u == 0) return step;
                for (int r=0; r<m; r++) for (int c=0; c<n; c++) {
                    int v = u; v ^= (1 << (r * n + c));
                    if (r-1>=0) v ^= (1 << ((r-1) * n + c));
                    if (r+1<m) v ^= (1 << ((r+1) * n + c));
                    if (c-1>=0) v ^= (1 << (r * n + c - 1));
                    if (c+1<n) v ^= (1 << (r * n + c+1));
                    if (vis.insert(v).second) nxt.emplace_back(v);
                }
            }
            q = move(nxt); step ++;
        }

        return -1;    

    }
};