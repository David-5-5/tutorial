#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        // 自行解答 哈希 + TLE
        int n = nums.size();
        vector<vector<pair<int ,int>>> g(n);
        for (auto & e : edges) {
            auto & u = e[0], &v = e[1], & w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        int mx_path = 0, mn_nodes = INT_MAX;
        
        vector<pair<int, int>> pres = {{0, nums[0]}};                    // 路径的前缀和
        vector<int> start = {0};                   // 路径中当前节点的起点
        unordered_map<int, int> cnt;
        cnt[nums[0]] ++;
        int twice_cnt = 0;
        auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
            for (auto & [v, w]: g[u]) {
                if (v == fa) continue;
                auto color = nums[v];
                auto v_start = start.back();
                cnt[color] += 1;
                if (cnt[color] == 2) twice_cnt ++;
                while (cnt[color] > 2 || twice_cnt == 2) {
                    if (cnt[pres[v_start].second] == 2) twice_cnt -= 1;
                    cnt[pres[v_start].second] --; v_start ++;
                }

                pres.emplace_back(pres.back().first + w, color);
                start.emplace_back(v_start);
                auto path = pres.back().first - pres[v_start].first, nodes = (int)start.size() - v_start;
                if (path > mx_path) {
                    mx_path = path; mn_nodes = nodes;
                } else if (path == mx_path) mn_nodes = min(mn_nodes, nodes);
                
                dfs(v, u);

                // 恢复现场
                cnt[pres.back().second] --; if (cnt[pres.back().second] == 1) twice_cnt --;
                pres.pop_back(); auto l = start.back(); start.pop_back();
                while (l > start.back()) {
                    l --; cnt[pres[l].second] ++;
                    if (cnt[pres[l].second] == 2) twice_cnt ++;
                }
            }
        };

        dfs(0, -1);

        return {mx_path, mn_nodes};        
    }

    vector<int> longestSpecialPath2(vector<vector<int>>& edges, vector<int>& nums) {
        // 自行解答 LAST
        int n = nums.size();
        vector<vector<pair<int ,int>>> g(n);
        for (auto & e : edges) {
            auto & u = e[0], &v = e[1], & w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        int mx_path = 0, mn_nodes = INT_MAX;
        unordered_map<int, vector<int>> last;   // 路径中相同的 nums[i]
        last[nums[0]].emplace_back(0);          // 根

        vector<int> pres = {0};                    // 路径的前缀和
        vector<int> start = {0};                   // 路径中当前节点的起点
        vector<int> twice = {-1};                  // 
        auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
            for (auto & [v, w]: g[u]) {
                if (v == fa) continue;
                auto color = nums[v];
                // cout << u << ", " << v << endl;
                auto v_start = start.back();
                if (last[color].size()>1 && last[color][last[color].size()-2] + 1 > v_start) {
                    v_start = last[color][last[color].size()-2] + 1;
                }
                
                if (last[color].size() < 1 || last[color].back() < v_start) {
                    twice.emplace_back(twice.back());
                } else {
                    if (twice.back() == -1) twice.emplace_back(color);
                    else {
                        auto prv_c = twice.back();
                        auto prv_l = last[prv_c].size();
                        if (last[prv_c][prv_l-2] < v_start) {
                            twice.emplace_back(color);
                        } else {
                            v_start = min(last[color].back(), last[prv_c][prv_l-2]) + 1;
                            if (last[color].back()>last[prv_c][prv_l-2]) twice.emplace_back(color);
                            else twice.emplace_back(twice.back());
                        }
                    }
                }
                last[color].emplace_back(pres.size());
                pres.emplace_back(pres.back() + w);
                start.emplace_back(v_start);
                auto path = pres.back() - pres[v_start], nodes = (int)start.size() - v_start;
                if (path > mx_path) {
                    mx_path = path; mn_nodes = nodes;
                } else if (path == mx_path) mn_nodes = min(mn_nodes, nodes);
                
                dfs(v, u);

                // 恢复现场
                pres.pop_back(); start.pop_back(); last[color].pop_back(); twice.pop_back();
            }
        };

        dfs(0, -1);

        return {mx_path, mn_nodes};        
    }    
};