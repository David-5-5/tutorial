#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.4 并查集 - 数组上的并查集
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();

        vector<int> ans(n, 1);
        set<int> drys;  // set.lower_bound(val) 比 ranges::lower_bound(vector, val) 快很多
        unordered_map<int, int> mp;

        for (int i = 0; i < n; ++i) {
            if (rains[i] == 0) {
                // 遇到晴天，记录下晴天的日期
                drys.insert(i);
            } else {
                // 遇到下雨天，检查之前是否有该湖泊的雨
                ans[i] = -1;
                if (mp.count(rains[i])) {
                    // 如果有，找到最近的一个晴天来放水
                    auto it = drys.lower_bound(mp[rains[i]]);
                    if (it == drys.end()) return {};
                    ans[*it] = rains[i];
                    drys.erase(it);
                }
                mp[rains[i]] = i;
                
            }
        }

        return ans;
    }
};