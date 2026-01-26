#include <bits/stdc++.h>
using namespace std;

// 图论算法 二、拓扑排序 2.1 拓扑排序
class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // 自行解答 不过代码太乱了，需要重新梳理
        vector<int> ed(n); vector<int> gd(m);
        vector<set<pair<int, int>>> eg(n); vector<set<pair<int, int>>> gg(m);
        unordered_map<int, vector<int>> g2e;
        for (int i=0; i<n; ++i) if (group[i]!=-1) g2e[group[i]].emplace_back(i);

        for (int u=0; u<n; ++u) {
            for (auto &v : beforeItems[u]) {
                if (group[v] == group[u]) {     //节点之间依赖
                    eg[v].insert({0, u}); ed[u] ++;            
                } else if (group[v] == -1 & group[u] != -1) { // 组依赖节点
                    if (eg[v].insert({1, group[u]}).second) gd[group[u]] ++;
                } else if (group[v] != -1 & group[u] == -1) { // 节点依赖组
                    if (gg[group[v]].insert({0, u}).second) ed[u] ++;
                }  else {                  // 组之间依赖
                    if (gg[group[v]].insert({1, group[u]}).second) gd[group[u]] ++;
                }
            }
        }
        
        vector<int> ans;
        deque<int> qe, qg;
        for (int i=0; i<n; ++i) if (ed[i] == 0 && group[i] == -1) qe.emplace_back(i);
        for (int i=0; i<m; ++i) if (gd[i] == 0) qg.emplace_back(i);
        
        while (!qe.empty() || !qg.empty()) {
            if (!qe.empty()) {
                auto u = qe.front(); qe.pop_front();
                ans.emplace_back(u);
                for (auto& [t, inx]: eg[u]) {
                    if (t == 0) {
                        ed[inx] --; if (ed[inx] == 0 ) qe.emplace_back(inx);
                    } else {
                        gd[inx] --; if (gd[inx] == 0) qg.emplace_back(inx);
                    }
                }
            }
            if (!qg.empty()) {
                auto u = qg.front(); qg.pop_front();
                
                for (auto& [t, inx]: gg[u]) {
                    if (t == 0) {
                        ed[inx] --; if (ed[inx] == 0) qe.emplace_back(inx);
                    } else {
                        gd[inx] --; if (gd[inx] == 0) qg.emplace_back(inx);
                    }
                }
                deque<int> ing;
                for (auto & v: g2e[u]) {
                    if (ed[v] == 0) ing.emplace_back(v);
                }
                while (!ing.empty()) {
                    auto gu = ing.front(); ing.pop_front();
                    ans.emplace_back(gu);
                    for (auto& [_, inx]: eg[gu]) {
                        if (group[inx] == u) {
                            ed[inx] --; if (ed[inx] == 0) ing.emplace_back(inx);
                        } else {
                            ed[inx] --; if (ed[inx] == 0) qe.emplace_back(inx);
                        }
                    }
                }
            }
        }
        // return ans;
        return ans.size() == n? ans: vector<int>();  
    }
};