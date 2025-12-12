#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        // 自行解答 由外向内
        int m = board.size(), n = board[0].size();
        auto dfs = [&](this auto&& dfs, int x, int y) -> void {
            if (x <0 || x >=m || y<0 || y >= n || board[x][y] != 'O') return;

            board[x][y] = 'A';
            dfs(x+1, y); dfs(x-1, y); dfs(x, y-1); dfs(x, y+1);
        };

        for (int i=0; i<m; ++i) {dfs(i, 0); dfs(i, n-1);}
        for (int j=1; j<n-1; ++j) {dfs(0, j); dfs(m-1, j);}


        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (board[i][j] == 'A') board[i][j] = 'O';
            else if (board[i][j] == 'O') board[i][j] = 'X';
        }
    }
};