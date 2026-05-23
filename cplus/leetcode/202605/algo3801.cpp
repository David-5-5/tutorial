#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // translate from python by doubao
    long long minMergeCost(vector<vector<int>>& lists) {
        int n = lists.size();
        int max_mask = 1 << n;

        long long len[max_mask];
        int med[max_mask];
        long long dp[max_mask];
        
        memset(len, -1, sizeof(len));
        memset(med, -1, sizeof(med));
        memset(dp, -1, sizeof(dp));

        function<long long(int)> get_len = [&](int mask) -> long long {
            if (len[mask] != -1) return len[mask];
            long long res = 0;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) 
                    res += (long long)lists[j].size();
            }
            return len[mask] = res;
        };

        function<int(int)> get_med = [&](int mask) -> int {
            if (med[mask] != -1) return med[mask];
            long long cnt = (get_len(mask) + 1) / 2;

            int l = INT_MAX, r = INT_MIN;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) {
                    l = min(l, lists[j][0]);
                    r = max(r, lists[j].back());
                }
            }
            l--; r++;

            while (l + 1 < r) {
                long long mid = (1LL * l + r) / 2;
                long long res = 0;
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) {
                        res += upper_bound(lists[j].begin(), lists[j].end(), (int)mid) 
                               - lists[j].begin();
                    }
                }
                if (res >= cnt) r = (int)mid;
                else l = (int)mid;
            }

            int res = INT_MIN;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) {
                    int pos = upper_bound(lists[j].begin(), lists[j].end(), r) 
                              - lists[j].begin();
                    if (pos > 0) res = max(res, lists[j][pos - 1]);
                }
            }
            return med[mask] = res;
        };

        function<long long(int)> dfs = [&](int st) -> long long {
            if (__builtin_popcount(st) == 1) return 0;
            if (dp[st] != -1) return dp[st];

            long long ans = LLONG_MAX;
            for (int i = (st - 1) & st; i > st / 2; i = (i - 1) & st) {
                long long cost = dfs(i) + dfs(st - i) 
                               + get_len(st) 
                               + abs((long long)get_med(i) - get_med(st - i));
                ans = min(ans, cost);
            }
            return dp[st] = ans;
        };

        return dfs((1 << n) - 1);
    }
};