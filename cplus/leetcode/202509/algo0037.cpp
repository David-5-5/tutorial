#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.5 排列型回溯
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        // 自行解答（回溯）
        auto check = [&] (int i, int j, char val) -> bool {
            for (int k=0; k<9; k++) if (board[i][k] == val) return false;
            for (int k=0; k<9; k++) if (board[k][j] == val) return false;
            for (int u=0; u<3; ++u) for (int v=0; v<3; ++v)
                if (board[u+(i/3)*3][v+(j/3)*3] == val) return false;
            
            return true;
        };
        vector<pair<int,int>> fills;
        for (int i=0; i<9; ++i) for (int j=0; j<9; ++j) {
            if (board[i][j] == '.') fills.emplace_back(i, j);
        }
        int n = fills.size();

        auto dfs = [&] (this auto&& dfs, int i) -> bool {
            if (i == n) return true;
            for (int k = 0; k<9; ++k) {
                auto& [x, y] = fills[i];
                
                if (check(x, y, k+'1')) {
                    board[x][y] = k + '1';
                    if (dfs(i+1)) return true;
                    board[x][y] = '.';
                }
                
            }
            return false;
        };
        dfs(0);

    }
    
};