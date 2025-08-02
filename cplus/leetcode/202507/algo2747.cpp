#include <bits/stdc++.h>
using namespace std;

// 双周赛 107
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        unordered_map<int, int> cnt;
        
        sort(logs.begin(), logs.end(), [&](const auto& a, const auto& b){
            return a[1] < b[1];
        });

        int m = queries.size(), idx[m];
        iota(idx, idx + m, 0);
        sort(idx, idx + m, [&](int i, int j){
            return queries[i] < queries[j];
        });

        int l = 0, r=0; // pointer of logs
        vector<int> ans(m);
        for (int i=0; i<m; ++i) {
            auto id = idx[i];
            // 入窗口
            while (r < logs.size() && logs[r][1] <= queries[id]) {
                ++cnt[logs[r][0]];
                r ++;
            }            
            // 出窗口
            while (l < r && queries[id] - logs[l][1] > x) {
                --cnt[logs[l++][0]];
                if (cnt[logs[l-1][0]] == 0)
                    cnt.erase(logs[l-1][0]);
            }
            ans[id] = n - cnt.size();
        }

        return ans;
    }
};
