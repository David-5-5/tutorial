#include <bits/stdc++.h>
using namespace std;

// 图论算法 五、欧拉路径/欧拉回路
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // 自行解答，复习
        unordered_map<string, multiset<string>> graph;
        for (auto t: tickets) {
            graph[t[0]].insert(t[1]);
        }

        vector<string> ans;
        auto dfs = [&](this auto&& dfs, string u) -> void {
            while (!graph[u].empty()) {
                auto v = *graph[u].begin(); graph[u].erase(graph[u].begin());
                dfs(v);
            }
            ans.emplace_back(u);
        };
        dfs("JFK"); 
        reverse(ans.begin(), ans.end()); return ans;
    }
};