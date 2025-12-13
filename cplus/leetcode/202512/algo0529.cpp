#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        const int dirs[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        int m = board.size(), n = board[0].size();

        auto count = [&] (int x, int y) -> int {
            int res = 0;
            for (auto& d: dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >=0 && nx <m && ny>=0 && ny < n && board[nx][ny] == 'M')  res++;
            }
            return res;
        };

        auto dfs = [&](this auto&& dfs, int x, int y) -> void {
            if (board[x][y] == 'M') {
                board[x][y] = 'X'; return;
            } else if (board[x][y] == 'E') {
                int res = count(x, y);
                if (res) {board[x][y] = '0' + res; return;}
                else board[x][y] = 'B';
            } else return;
            
            for (auto& d: dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >=0 && nx <m && ny>=0 && ny < n && board[nx][ny] == 'E')  dfs(nx, ny);
            }            
        };

        dfs(click[0], click[1]);

        return board;
    }
};