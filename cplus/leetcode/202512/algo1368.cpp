#include <bits/stdc++.h>
using namespace std;

// 三、网格图 0-1 BFS
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        // 自行解答，想了好半天
        unordered_map<int, pair<int, int>> dirs = {
            {1, pair<int, int>{0, 1}},
            {2, pair<int, int>{0, -1}},
            {3, pair<int, int>{1, 0}},
            {4, pair<int, int>{-1, 0}}
        };
        int m = grid.size(), n = grid[0].size();

        vector cost(m, vector<int>(n, INT_MAX/2)); 
        vector<tuple<int, int, int>> q; // tuple : x, y, cost
        q.emplace_back(0, 0, 0); 
        cost[0][0] = 0;
        while (!q.empty()) {
            vector<tuple<int, int, int>> nxt;
            for (auto& [x, y, c]: q) {
                
                for (auto d : dirs) {
                    int cur_cost = 0;
                    if (d.first != grid[x][y]) cur_cost = 1;    // 这里是关键点，变更方向需要+1
                    int dx = x + d.second.first, dy = y + d.second.second;

                    if (dx>=0 && dx<m && dy>=0 && dy<n && cur_cost+c < cost[dx][dy]){
                        cost[dx][dy] = cur_cost+c;
                        nxt.emplace_back(dx, dy, cost[dx][dy]);
                    }
                }
            }            
            q = move(nxt);;
        }

        return cost[m-1][n-1];
    }

    int minCost2(vector<vector<int>>& grid) {
        // 自行解答， 使用 priority_queue 按照当前 cost优先出队列优化
        unordered_map<int, pair<int, int>> dirs = {
            {1, pair<int, int>{0, 1}},
            {2, pair<int, int>{0, -1}},
            {3, pair<int, int>{1, 0}},
            {4, pair<int, int>{-1, 0}}
        };
        int m = grid.size(), n = grid[0].size();

        vector cost(m, vector<int>(n, INT_MAX/2)); 

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, 
            greater<tuple<int, int, int>>> q; // tuple : cost, x, y
        cost[0][0] = 0;
        q.emplace(cost[0][0], 0, 0);
        while (!q.empty()) {
            auto [c, x, y] = q.top(); q.pop();
            if (x == m-1 && y == n-1) return c; // 提前返回
            if (c > cost[x][y]) continue;       // 延迟删除
            for (auto d : dirs) {
                int cur_cost = 0;
                if (d.first != grid[x][y]) cur_cost = 1;
                int dx = x + d.second.first, dy = y + d.second.second;

                if (dx>=0 && dx<m && dy>=0 && dy<n && cur_cost+c < cost[dx][dy]){
                    cost[dx][dy] = cur_cost+c;
                    q.emplace(cost[dx][dy], dx, dy);
                }
            }
        }            

        return -1; 
    }    
};