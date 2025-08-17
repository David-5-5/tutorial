#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 专题 - 离线算法
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        sort(items.begin(), items.end());
        int mx = 0;
        
        int l = 0, n = items.size(), m = queries.size();
        int idx[m];
        iota(idx, idx+m, 0);
        sort(idx, idx + m, [&](int i, int j) {
            return queries[i] < queries[j];
        });

        vector<int> ans(m);
        for (int i : idx) {
            while (l < n && items[l][0] <= queries[i]) {
                mx = max(mx, items[l++][1]);
            }
            ans[i] = mx;
        }

        return  ans;     
    }
};