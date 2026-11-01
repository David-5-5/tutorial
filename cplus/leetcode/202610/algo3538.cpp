#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        // translate from python by doubao
        int sz_t = 101, sz_i = n, sz_K = k+1, sz_acc = 101;
        int total = sz_t * sz_i * sz_K * sz_acc;
        vector<int> memo(total, -1);

        auto dfs = [&](this auto&& dfs, int t, int i, int K, int acc) -> int {
            if (K < 0) return INT_MAX / 2;
            if (i == n-1) {
                if(K == 0) return t * (l - position[i-1]);
                return INT_MAX / 2;
            }
            int idx = t * sz_i * sz_K * sz_acc + i * sz_K * sz_acc + K * sz_acc + acc;
            if(memo[idx] != -1) return memo[idx];
            int cost = t * (position[i] - position[i-1]);
            return memo[idx] = cost + min(dfs(time[i]+acc, i+1, K, 0), dfs(t, i+1, K-1, acc+time[i]));
        };
        int ans = dfs(time[0], 1, k, 0);
        return ans;
    }
};