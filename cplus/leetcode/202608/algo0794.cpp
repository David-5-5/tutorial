#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int x = 0, o = 0; bool xwin = false, owin = false;
        for (int i=0; i<3; i++) for (int j=0; j<3; j++) {
            if (board[i][j] == 'X') x ++;
            else if (board[i][j] == 'O') o ++;
        }

        auto check = [&](char ch) -> bool {
            for (int i=0; i<3; i++) {
                if (board[i][0]==ch && board[i][1]==ch && board[i][2]==ch) return true;
                if (board[0][i]==ch && board[1][i]==ch && board[2][i]==ch) return true;
            }
            if (board[0][0] == ch && board[1][1] == ch && board[2][2] == ch) return true;
            if (board[0][2] == ch && board[1][1] == ch && board[2][0] == ch) return true;

            return false;
        };
        xwin = check('X'); owin = check('O');
        if (xwin && owin) return false;
        if (xwin) return x == o + 1;
        if (owin) return x == o;
        return x == o || x == o + 1;
    }
};