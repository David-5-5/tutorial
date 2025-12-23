#include <bits/stdc++.h>
using namespace std;

// 三、网格图 0-1 BFS
class Solution {
public:
    int conveyorBelt(vector<string>& matrix, vector<int>& start, vector<int>& end) {
        // 自行解答， 同 1368
        unordered_map<char, pair<int, int>> dirs = {
            {'>', pair<int, int>{0, 1}},
            {'<', pair<int, int>{0, -1}},
            {'v', pair<int, int>{1, 0}},
            {'^', pair<int, int>{-1, 0}}
        };
        int m = matrix.size(), n = matrix[0].size();

        vector cost(m, vector<int>(n, INT_MAX/2)); 
        vector<tuple<int, int, int>> q; // tuple : x, y, cost
        q.emplace_back(start[0], start[1], 0); 
        cost[start[0]][start[1]] = 0;
        while (!q.empty()) {
            vector<tuple<int, int, int>> nxt;
            for (auto& [x, y, c]: q) {
                
                for (auto d : dirs) {
                    int cur_cost = 0;
                    if (d.first != matrix[x][y]) cur_cost = 1;
                    int dx = x + d.second.first, dy = y + d.second.second;

                    if (dx>=0 && dx<m && dy>=0 && dy<n && cur_cost+c < cost[dx][dy]){
                        cost[dx][dy] = cur_cost+c;
                        nxt.emplace_back(dx, dy, cost[dx][dy]);
                    }
                }
            }            
            q = move(nxt);;
        }

        return cost[end[0]][end[1]];
    }
};
