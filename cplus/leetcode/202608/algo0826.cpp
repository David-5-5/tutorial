#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        // 二分查找
        int n = difficulty.size(), m = worker.size(), idx[n]; iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return difficulty[i] < difficulty[j];
        });

        int mx_profit = 0;
        for (int i=0; i<n; i++) {
            auto id = idx[i];
            mx_profit = max(mx_profit, profit[id]);
            profit[id] = mx_profit;
        }
        sort(difficulty.begin(), difficulty.end()); sort(profit.begin(), profit.end());

        int ans = 0;
        for (int i=0; i<m; i++) {
            auto it = ranges::upper_bound(difficulty.begin(), difficulty.end(), worker[i]);
            if (it == difficulty.begin()) continue;
            ans += profit[prev(it) - difficulty.begin()];
        }
        return ans;     
        
    }

};