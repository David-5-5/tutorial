#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.3 图论建模 + BFS 最短路
class Solution {
public:
    int minJumps(vector<int>& arr) {
        // 自行解答，BFS
        int n = arr.size(); unordered_map<int, vector<int>> v_ids; set<int> v_vis;
        for (int i=0; i<n; ++i) v_ids[arr[i]].emplace_back(i);
        vector<int> q = {0}; int step = 0; vector<bool> vis(n); vis[0] = true;

        while (!q.empty()) {
            vector<int> nxt;
            for (auto& u: q) {
                if (u == n-1) return step;
                if (u-1>=0 && !vis[u-1]) nxt.emplace_back(u-1);
                if (!vis[u+1]) nxt.emplace_back(u+1);
                if (!v_vis.count(arr[u])) {     // 值相同的节点遍历一次!!
                    v_vis.insert(arr[u]);
                    for (auto& v: v_ids[arr[u]]) {
                        if (!vis[v]) {
                            vis[v] = true;
                            nxt.push_back(v);
                        }
                    }
                }
            }

            q = move(nxt); step ++;
        }

        return -1;
    }
};