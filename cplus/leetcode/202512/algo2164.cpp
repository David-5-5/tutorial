#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        // 自行解答
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));
        vector<pair<int, int>> q;
        q.emplace_back(start[0], start[1]);
        int low = pricing[0], high = pricing[1];

        vector<tuple<int, int, int, int>> candi; int dis = 0;
        int price = grid[start[0]][start[1]];
        vis[start[0]][start[1]] = true;
        if (price >= low && price <= high) candi.emplace_back(dis, price, start[0], start[1]);

        while (!q.empty()) {
            dis++;
            vector<pair<int, int>> nxt;
            for (auto& [x, y]: q) {
                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<m && dy>=0 && dy<n && !vis[dx][dy] && grid[dx][dy]!=0){
                        vis[dx][dy] = true;
                        price = grid[dx][dy];
                        if (price >= low && price <= high) candi.emplace_back(dis, price, dx, dy);
                        nxt.emplace_back(dx, dy);
                    }
                }
            }
            q = move(nxt); 
        }
        sort(candi.begin(), candi.end()); vector<vector<int>> ans; 
        for (int i=0; i<k && i<candi.size(); ++i) {
            ans.push_back({get<2>(candi[i]), get<3>(candi[i])});
        }
        return ans;         
    }
};