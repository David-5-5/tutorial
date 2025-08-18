#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 专题 - 离线算法
class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        // 复习 - 自行解答
        sort(rooms.begin(), rooms.end(), [](const auto& a, const auto& b) {
             return a[1] > b[1];
        });

        int l = 0, n = rooms.size(), m = queries.size();
        int idx[m];
        iota(idx, idx+m, 0);
        sort(idx, idx + m, [&](int i, int j) {
            return queries[i][1] > queries[j][1];
        });

        set<int> r_ids; vector<int> ans(m);
        for (int i=0; i<m; i++) {
            int id = idx[i];
            while (l < n && rooms[l][1] >= queries[id][1]) {
                r_ids.insert(rooms[l++][0]);
            }
            if (r_ids.empty()) {
                ans[id] = -1;
            } else {
                auto it = r_ids.lower_bound(queries[id][0]);
                if (it == r_ids.end()) {
                    ans[id]  = *prev(it);
                } else if (it == r_ids.begin()) {
                    ans[id]  = *it;
                } else {
                    ans[id] = *it - queries[id][0] < queries[id][0] - *prev(it)? *it : *prev(it);
                }
            }
        }
        return ans; 
    }
};