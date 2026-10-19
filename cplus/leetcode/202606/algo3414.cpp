#include <bits/stdc++.h>
using namespace std;

// 七、其他线性 DP - 7.2 不相交区间
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        // 从 python 用豆包翻译过来
        int n = intervals.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return intervals[a][1] < intervals[b][1];
        });

        vector<int> rs;
        rs.push_back(-1);
        for (int i : idx) rs.push_back(intervals[i][1]);

        const long long INF = 1e18;
        vector<vector<long long>> dp(n + 1, vector<long long>(5, -INF));
        vector<vector<int>> last(n + 1, vector<int>(5, -1));
        dp[0][0] = 0;

        for (int i = 0; i < n; ++i) {
            int l = intervals[idx[i]][0];
            int w = intervals[idx[i]][2];
            for (int k = 0; k < 5; ++k) {
                dp[i+1][k] = dp[i][k];
            }
            int pi = lower_bound(rs.begin(), rs.end(), l) - rs.begin() - 1;
            for (int k = 0; k < 4; ++k) {
                if (dp[pi][k] == -INF) continue;
                if (w + dp[pi][k] >= dp[i+1][k+1]) {
                    last[i+1][k+1] = pi;
                    dp[i+1][k+1] = w + dp[pi][k];
                }
            }
        }

        long long mx = -INF;
        for (int k = 1; k <=4; ++k) mx = max(mx, dp[n][k]);

        using Key = tuple<int, int, long long>;
        map<Key, vector<int>> memo;

        function<vector<int>(int, int, long long)> trace = [&](int i, int k, long long score) -> vector<int> {
            if (i == 0 || k == 0 || score == 0) return {};
            Key key = {i, k, score};
            if (memo.count(key)) return memo[key];

            int w = intervals[idx[i-1]][2];
            vector<vector<int>> res;

            if (dp[i][k] == score && last[i][k] >= 0) {
                auto sub = trace(last[i][k], k-1, score - w);
                sub.push_back(idx[i-1]);
                sort(sub.begin(), sub.end());
                res.push_back(sub);
            }
            if (dp[i-1][k] == score) {
                auto sub = trace(i-1, k, score);
                res.push_back(sub);
            }
            return memo[key] = *min_element(res.begin(), res.end());
        };

        vector<vector<int>> candidates;
        for (int k = 1; k <=4; ++k) {
            if (dp[n][k] == mx) {
                candidates.push_back(trace(n, k, mx));
            }
        }
        return *min_element(candidates.begin(), candidates.end());
    }

    vector<int> maximumWeight2(vector<vector<int>>& intervals) {
        // int n = intervals.size();

        // int idx[n];
        // iota(idx, idx+n, 0);
        // sort(idx, idx + n, [&](int i, int j) {
        //     return intervals[i][1] < intervals[j][1];
        // });

        // vector<int> rs = {-1};
        // for (int i=0; i<n; i++) rs.emplace_back(intervals[idx[i]]);

        // vector<array<pair<long long, vector<int>>, 5>> dp(n + 1);

        // for (int i=0; i<n; i++) {
        //     auto l = intervals[idx[i]][0], w = intervals[idx[i]][2];
        //     for (int k=0; k<5; k++) {
        //         dp[i+1][k] = dp[i][k];
        //     }
        //     auto p = lower_bound(rs.begin(), rs.end(), l) - rs.begin() - 1;
        //     for (int k = 0; k<4; k++) {
        //         dp[i+1][k+1] = min(dp[p][k], {});
        //     }   
        // }
    }    
};