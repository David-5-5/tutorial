#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        // 自行解答
        unordered_map<string, vector<pair<string, double>>> g1, g2;
        int m = pairs1.size(), n = pairs2.size();
        for (int i=0; i<m; i++) {
            g1[pairs1[i][0]].emplace_back(pairs1[i][1], rates1[i]);
            g1[pairs1[i][1]].emplace_back(pairs1[i][0], 1/rates1[i]);
        }
        for (int i=0; i<n; i++) {
            g2[pairs2[i][0]].emplace_back(pairs2[i][1], rates2[i]);
            g2[pairs2[i][1]].emplace_back(pairs2[i][0], 1/rates2[i]);
        }
        double mx = 1.0;

        auto dfs2 = [&](this auto&& dfs2, string& cur, string fa, double v) -> void {
            if (cur == initialCurrency) {
                mx = max(mx, v); return;
            }
            for (auto& [nx_cur, rate]: g2[cur]) {
                if (nx_cur == fa) continue;
                dfs2(nx_cur, cur, v * rate);
            }
        };


        auto dfs1 = [&](this auto&& dfs1, string& cur, string fa, double v) -> void {
            for (auto& [nx_cur, rate]: g1[cur]) {
                if (nx_cur == fa) continue;

                dfs2(nx_cur, "", v*rate);
                dfs1(nx_cur, cur, v * rate);
            }
        };

        dfs1(initialCurrency, "", 1.0);
        
        return mx;       
    }
};