#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        vector<int> ans(n, -1);
        for (int i=0; i<n; i++) {
            int r = 0, c = i; bool pass = true;
            for (int r=0; r<m; r++) {
                if (grid[r][c] == 1) {
                    if (c + 1 == n || grid[r][c+1] == -1) {pass = false; break;}
                    else c ++;
                } else {
                    if (c - 1 < 0 || grid[r][c-1] == 1)  {pass = false; break;}
                    else c--;
                }
            }
            if (pass) ans[i] = c;
        }

        return ans;        
    }
};