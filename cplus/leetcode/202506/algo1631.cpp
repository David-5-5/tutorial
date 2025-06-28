#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.2 堆 - 进阶
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        // 自行解答 
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int n = heights.size(), m = heights[0].size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        vector vis(n, vector<int>(m));
        int ans = 0;
        pq.emplace(0, 0, 0);
        while (!pq.empty()) {
            auto [v, r, c] =  pq.top(); pq.pop();
            ans = max(v, ans);
            if (vis[r][c]) continue;
            vis[r][c] = true;
            if (r == n-1 && c == m-1) return ans;
            for (int i=0; i<4; ++i) {
                int nr = r + dirs[i][0], nc = c + dirs[i][1];
                if (nr >=0 && nr < n && nc>=0 && nc<m && !vis[nr][nc]) {
                    pq.emplace(abs(heights[r][c]-heights[nr][nc]), nr, nc);
                }
            }
        }

        return 0;   // 仅编译要求
    }
};