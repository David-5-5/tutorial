#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 其他
class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        // 参考题解
        int n = board.size();
        vector<int>& first_row =  board[0];
        vector<int> first_col(n);

        // 统计第一行，第一列的 1 的数目
        int row_1 = 0, col_1 = 0;
        for (int i=0; i<n; i++) {
            first_col[i] = board[i][0];
            if (first_col[i]) col_1 ++;
            if (first_row[i]) row_1 ++;
        }
        
        // 0, 1 数据仅差 1
        if (abs(row_1*2-n) > 1 || abs(col_1*2-n)>1) return -1;

        auto compair = [&](vector<int>& comp1, vector<int>& comp2, bool equal) {
            for (int i=0; i<comp1.size(); i++ )
                if (equal && comp1[i] != comp2[i]) return false;
                else if (!equal && comp1[i] == comp2[i]) return false;
            
            return true;
        };

        // 检查其余行，列和第一行，列的关系，要么完全相同，要么完全不同
        int r_eq = 1, r_n_eq = 0, c_eq = 1, c_n_eq = 0;
        for (int i=1; i<n; i++) {
            if (compair(first_row, board[i], true)) r_eq ++;
            else if (compair(first_row, board[i], false)) r_n_eq ++;
            else return -1;
            vector<int> col(n);
            for (int j=0 ; j<n; j++) col[j] = board[j][i];
            if (compair(first_col, col, true)) c_eq ++;
            else if (compair(first_col, col, false)) c_n_eq ++;
            else return -1;            
        }

        if (abs(r_eq - r_n_eq)>1 || abs(c_eq - c_n_eq)>1) return -1;
        
        int ans = 0;
        vector<int> t1((n/2)*2);
        vector<int> t2((n/2)*2);
        for (int i=0; i<n/2; i++ ){
            t1[2*i] =1,  t2[2*i+1] = 1;
            t1[2*i+1]=0, t2[2*i] = 0;
        }

        auto cnt = [&](vector<int> arr1, vector<int> arr2) -> int {
            int diff = 0;
            for (int i=0; i<arr1.size();i++) {
                if (arr1[i] != arr2[i]) diff++;
            }
            return diff;
        };
        
        if (n % 2 == 0) {
            cout << "this" << endl;
            return min(cnt(first_row, t1), cnt(first_row,t2))/2 + 
                min(cnt(first_col, t1), cnt(first_col,t2))/2;
        }

        t1.push_back(1); t2.push_back(0);
        int move_row = 0, move_col = 0;
        if (row_1 * 2 < n) 
            move_row = cnt(first_row, t2)/2;
        else 
            move_row = cnt(first_row, t1)/2;
        
        if (col_1 * 2 < n) 
            move_col = cnt(first_col, t2)/2;
        else 
            move_col = cnt(first_col, t1)/2;

        return move_row + move_col;
    }

};