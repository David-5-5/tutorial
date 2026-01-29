#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    long long maxTotal(vector<int>& value, vector<int>& limit) {
        int n = value.size(), idx[n];
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            if (limit[i] == limit[j]) return value[i] > value[j];
            return limit[i] < limit[j];
        });
        long long ans = 0; int x = 0;
        multiset<int> actives;
        for (int i=0; i<n; ++i) {
            auto id = idx[i];

            if (actives.size() < limit[id] && x < limit[id]) {
                actives.insert(limit[id]);
                ans += value[id]; 
                x = max(x, (int) actives.size());
                for (auto it=actives.begin(); it!=actives.end(); it=actives.erase(it)) {
                    if (*it > x) break;
                }
            }
        }

        return ans;   
    }
};