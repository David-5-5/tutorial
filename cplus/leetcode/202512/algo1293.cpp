#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        // 自行解答 
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int m = grid.size(), n = grid[0].size();
        // bfs 情况下，距离是越来越大，但是如果障碍越来越少，还是可以再次通过 (x, y)
        // int of obstacle 代替 bool visited,
        vector obstacle(m, vector<int>(n, k+1));    // 这个数据结构的构造还是很巧妙的！
        vector<tuple<int, int, int>> q; // tuple : x, y, count of obstacle
        q.emplace_back(0, 0, 0); 
        
        int dis = 0;
        while (!q.empty()) {
            vector<tuple<int, int, int>> nxt;
            for (auto& [x, y, ob]: q) {
                if (x == m-1 && y == n-1 && ob <= k) return dis;
                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<m && dy>=0 && dy<n && grid[dx][dy]+ob < obstacle[dx][dy]){
                        obstacle[dx][dy] = grid[dx][dy]+ob;
                        nxt.emplace_back(dx, dy, obstacle[dx][dy]);
                    }
                }
            }            
            q = move(nxt); dis ++;
        }

        return -1;        
    }
};