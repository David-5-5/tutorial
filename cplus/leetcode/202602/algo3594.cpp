#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        // 自行解答 2602
        auto comb_mx = [&](int state, int bits) -> vector<pair<int,int>> {
            vector<pair<int,int>> ans;
            if (__builtin_popcount(state) <= bits) {
                int mx = 0;
                for (int i=0; i<n; ++i) if ((state >> i) & 1) mx = max(mx, time[i]);
                ans.emplace_back(state, mx);
                return ans;
            }

            auto dfs = [&](this auto&& dfs, int i, int val, int mx) -> void {
                if (__builtin_popcount(val) == bits) {
                    ans.emplace_back(val, mx);
                    return;
                }
                if (i == n) return;
                dfs(i+1, val, mx);      // 不选
                if ((state >> i) & 1) {   // 选
                    dfs(i+1, val |= 1 << i, max(mx, time[i]));
                }
            };

            dfs(0, 0, 0);
            return ans;
        };
        int tot = (1 << n) - 1;

        vector dis(2, vector(1<<n, vector<double>(m, numeric_limits<double>::max())));
        dis[0][tot][0] = 0.0;
        priority_queue<tuple<double, int, int, int>, vector<tuple<double, int, int, int>>, greater<>> pq;
        pq.emplace(0.0, 0, tot, 0);
        while (!pq.empty()) {
            auto [t, d, s, cur_m] = pq.top(); pq.pop();
            if (t > dis[d][s][cur_m]) continue;
            if (d == 0) {
                for (int n_k=1; n_k<=k; n_k++) {
                    for (auto & [sub, mx] : comb_mx(s, n_k)) {
                        auto op_s = tot + sub - s;
                        double op_t = t + mx * mul[cur_m];
                        
                        auto op_m = (cur_m + (int)(mx * mul[cur_m])) % m;
                        if (op_t < dis[1][op_s][op_m]) {
                            dis[1][op_s][op_m] = op_t;
                            if (op_s < tot) pq.emplace(op_t, 1, op_s, op_m);
                        }
                    }
                }
            } else {
                for (auto & [sub, mx] : comb_mx(s, 1)) {
                    auto op_s = tot + sub - s;
                    double op_t = t + mx * mul[cur_m];
                    auto op_m = (cur_m + (int)(mx * mul[cur_m])) % m;
                    if (op_t < dis[0][op_s][op_m]) {
                        dis[0][op_s][op_m] = op_t;
                        pq.emplace(op_t, 0, op_s, op_m);
                    }
                }                
            }
        }
        
        double ans = ranges::min(dis[1][tot]);
        return ans == numeric_limits<double>::max()? - 1 : ans; 
    }
};