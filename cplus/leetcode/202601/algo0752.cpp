#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.3 图论建模 + BFS 最短路
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        // 自行解答
        set<string> vis(deadends.begin(), deadends.end());
        if (vis.count("0000")) return -1;

        vector<string> q = {"0000"}; vis.insert("0000"); int step = 0;
        while (!q.empty()) {
            vector<string> nxt;
            for (auto & u : q) {
                if (u == target) return step;

                for (int p=0; p<4; ++p) {
                    auto v = u; int cur = u[p] - '0';
                    v[p] = ((cur + 1) % 10) + '0'; 
                    if (vis.insert(v).second) nxt.push_back(v);
                    v[p] = ((cur + 9) % 10) + '0';
                    if (vis.insert(v).second) nxt.push_back(v);
                }
            }

            q = move(nxt); step ++;
        }
        return -1;   
    }
};