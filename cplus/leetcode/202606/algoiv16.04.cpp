#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string tictactoe(vector<string>& board) {
        // 分类讨论
        int m = board.size();

        bool hasEmpty = false;

        int cnt_d_o = 0, cnt_d_x = 0, cnt_a_o = 0, cnt_a_x = 0;
        for (int i=0; i<m; i++) {
            int cnt_r_o = 0, cnt_r_x = 0, cnt_c_o = 0, cnt_c_x = 0;
            if (board[i][i] == 'O') cnt_d_o ++;
            else if (board[i][i] == 'X') cnt_d_x ++;

            if (board[i][m-1-i] == 'O') cnt_a_o ++;
            else if (board[i][m-1-i] == 'X') cnt_a_x ++;
            
            for (int j=0; j<m; j++) {
                if (board[i][j] == 'O') cnt_r_o ++;
                else if (board[i][j] == 'X') cnt_r_x ++;
                else hasEmpty = true;

                if (board[j][i] == 'O') cnt_c_o ++;
                else if (board[j][i] == 'X') cnt_c_x ++;
            }
            if (cnt_r_o == m || cnt_c_o == m) return "O";
            if (cnt_r_x == m || cnt_c_x == m) return "X";
        }
        if (cnt_d_o == m || cnt_a_o == m) return "O";
        if (cnt_d_x == m || cnt_a_x == m) return "X";

        if (hasEmpty) return "Pending";
        else return "Draw";
    }
};