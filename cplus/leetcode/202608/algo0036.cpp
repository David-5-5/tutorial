#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        
        for (int i=0; i<9; i++) {   // 按行
            int rows = 0;
            for (int j=0; j<9; j++) {
                auto & x = board[i][j];
                if (x != '.') {
                    if ((rows & 1<< (x - '0')) == 0) rows |= 1<< (x - '0');
                    else {
                        return false;
                    }
                }
            }
        }
        for (int i=0; i<9; i++) {   // 按行
            int cols = 0;
            for (int j=0; j<9; j++) {
                auto & y = board[j][i];
                if (y != '.') {
                    if ((cols & 1<< (y - '0')) == 0) cols |=  1<< (y - '0');
                    else return false;
                }
            }
        }
        for (int i=0; i<9; i++) {   // 按九宫格
            int block = 0;
            for (int j=0; j<9; j++) {
                auto & x = board[3*(i/3)+j/3][3*(i%3)+j%3];
                if (x != '.') {
                    if ((block & 1<< (x - '0')) == 0) block |= 1<< (x - '0');
                    else return false;
                }
            }
        }

        return true;     
    }

};