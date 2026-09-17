#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        sort(items.begin(), items.end()); int n = items.size();
        unordered_map<int, int> factor_cnt;
        for (int i=0; i<n; i++) {
            auto x = items[i][0]; int mx = sqrt(x);
            if (x == 1) {
                factor_cnt[x] ++; continue;
            }
            for (int i=1; i<=mx; i++) {
                if (x % i) continue;
                if (factor_cnt.count(i)) factor_cnt[i] ++;
                if (i*mx != x && (i == 1 || factor_cnt.count(x/i))) factor_cnt[x/i] ++;
            }
        }
        int ans = 0;
        sort(items.begin(), items.end(), [](const vector<int>& a, const vector<int>& b){
            return a[1] < b[1];
        });

        int mn_price = items[0][1];
        for (auto& item: items) {
            auto & f = item[0], & p = item[1];
            // cout << f << ", " << factor_cnt[f] << endl;
            if (p >= mn_price * 2) break;
            if (factor_cnt[f] > 1) {
                auto cnt = min(budget / p, factor_cnt[f] - 1);
                ans += cnt * 2; budget -= cnt * p;
            }
        }

        return ans + budget/mn_price;
    }
};