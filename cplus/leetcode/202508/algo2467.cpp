#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = edges.size() + 1;
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        // 找出 bob 路径及其深度（time = 总深度-当前深度）
        unordered_map<int, int> bob_path; // key node_id, val = depth
        auto find_bob = [&](this auto&& f, int u, int fa, int d) -> bool {
            bool find = (u == bob);
            for (auto& v: g[u]) {
                if (v == fa) continue;
                if (find || f(v, u, d+1)) {find = true; break;}
            }
            if (find) {
                bob_path[u] = d; return true;
            }else return false;
        };
        find_bob(0, -1, 0);
        
        int ans = INT_MIN / 2, bob_d = bob_path.size()-1;

        auto dfs = [&](this auto&& dfs, int u, int fa, int d, int score) -> void {
            if (fa!=-1 && g[u].size() == 1) {ans = max(ans, score); return;} // 叶子节点，递归边界
            for (auto & v: g[u]) {
                if (v == fa) continue;
                int cur = amount[v];
                cout << v  << endl;
                if (bob_path.count(v)) {
                    if (d + 1 == bob_d - bob_path[v]) {
                        cur /= 2; // 平分减半
                    } else if (d+1 > bob_d - bob_path[v]) cur = 0; // 晚到得分为 0 
                }
                dfs(v, u, d+1, score+cur);
            }
        };
        dfs(0, -1, 0, amount[0]);
        return ans;        
    } 
};