#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        auto m = board.size(), n = board[0].size();
        vector next(board);

        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            int res = 0;
            if (i-1 >= 0 && j-1>=0) res += board[i-1][j-1];
            if (i-1 >=0) res += board[i-1][j];
            if (i-1 >=0 && j+1 <n) res += board[i-1][j+1];

            if (j-1 >= 0) res += board[i][j-1];
            if (j+1 < n) res += board[i][j+1];

            if (i+1 < m && j-1>=0) res += board[i+1][j-1];
            if (i+1 < m) res += board[i+1][j];
            if (i+1 < m && j+1 <n) res += board[i+1][j+1];

            if (res < 2 || res > 3) next[i][j] = 0;
            else if (res == 3) next[i][j] = 1;
        }

        board = move(next);    
    }
};