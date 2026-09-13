#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        sort(items.begin(), items.end()); int n = items.size();
        unordered_map<int, int> factor_cnt;
        int mn_price = INT_MAX;

        for (int i=0; i<n; i++) {
            mn_price = min(mn_price, items[i][1]);
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
        vector<pair<int, int>> nums;

        for (auto& item: items)  {
            auto & f = item[0], & p = item[1];
            if (factor_cnt[f] > 1) nums.emplace_back(p, factor_cnt[f]);
        }

        if (nums.size() == 0) return budget/mn_price;

        vector<int> f(budget+1);
        for (auto &[p, cnt]: nums) {
            for (int i=budget; i>=p; i--) {
                f[i] = max(f[i], f[i-p] + cnt);
            }
        }

        int ans = 0;
        for (int i=0; i<=budget; i++) {
            ans = max(ans, f[i] + (budget-i)/mn_price);
        }
        return ans;
    }
};