#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.3 图论建模 + BFS 最短路
class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        // 自行解答，BFS求最短路径
        if (startGene == endGene) return 0;

        int start = -1, end = -1, n = bank.size();
        for (int i=0; i<n; ++i) {
            if (endGene == bank[i]) end = i;
            if (startGene == bank[i]) start = i;
        }
        if (end == -1) return -1;
        if (start == -1) {bank.push_back(startGene); start = n; n++;}
        
        vector<vector<int>> g(n); vector<bool> vis(n); 
        for (int i=0; i<n-1; ++i) for (int j=i+1; j<n; ++j) {
            int d = 0;
            
            for (int k=0; k<8; ++k) if (bank[i][k] != bank[j][k]) d++;
            if (d == 1) {
                g[i].emplace_back(j); g[j].emplace_back(i);
            }
        }
        vector<int> q = {start}; vis[start] = true; int step = 0;
        while (!q.empty()) {
            vector<int> nxt;
            for (auto u: q) {
                if (u == end) return step;
                for (auto v: g[u]) if (!vis[v]) {
                    vis[v] = true; nxt.emplace_back(v);
                }
            }
            q = move(nxt); step ++;
        }

        return -1;  
    }
};