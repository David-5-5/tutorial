#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.2 广度优先搜索（BFS）
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        // 自行解答
        vector<vector<int>> gr(n), gb(n);
        for (auto& e:redEdges) gr[e[0]].push_back(e[1]);
        for (auto& e:blueEdges) gb[e[0]].push_back(e[1]);

        set<pair<int, int>> vis; vis.insert({0, 0}),  vis.insert({0, 1});
        vector<int> ans(n, -1); ans[0] = 0; int step = 0;
        vector<pair<int,int>> q = {{0, 0}, {0, 1}};

        while (!q.empty())  {
            vector<pair<int,int>> nxt; step ++;
            for (auto& [u, c]: q) {
                if (c == 0)  { // c == red
                    for (auto& v: gb[u]) if (vis.insert({v, 1}).second) {
                        if (ans[v]==-1)ans[v] = step; nxt.emplace_back(v, 1);
                    }
                } else { // c == blue
                    for (auto& v: gr[u]) if (vis.insert({v, 0}).second) {
                        if (ans[v]==-1) ans[v] = step; nxt.emplace_back(v, 0);
                    }
                }
            }

            q = move(nxt);
        }

        return ans;      

    }
};