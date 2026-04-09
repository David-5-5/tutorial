#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    int wardrobeFinishing(int m, int n, int cnt) {
        // 广度优先搜索
        deque<pair<int, int>> q; 

        vector vis(m, vector<bool>(n));
        auto check = [&](vector<int> vals) -> int {
            int res = 0;
            for (auto v: vals) {
                while (v) { res += v % 10; v /= 10;}
            }
            return res <= cnt;
        };

        int ans = 0;
        q.push_back({0, 0});  vis[0][0] = true;
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop_front();
            if (!check({x, y})) continue;
            ans += 1;
            if (x+1<m && !vis[x+1][y]) {q.push_back({x+1, y});vis[x+1][y] = true;}
            if (y+1<n && !vis[x][y+1]) {q.push_back({x, y+1});vis[x][y+1] = true;}
        }

        return ans;   
    }
};