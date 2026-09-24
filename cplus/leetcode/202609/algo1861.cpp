#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size(), n = boxGrid[0].size();
        vector ans(n, vector<char>(m, '.'));

        for (int r=m-1; r>=0; r--) {
            int nr = n - 1;
            for (int c=n-1; c>=0; c--) {
                if (boxGrid[r][c] == '#') {
                    ans[max(nr, c)][m-r-1] = '#';
                    nr = max(nr, c) - 1;
                } else if (boxGrid[r][c] == '*') {
                    ans[c][m-r-1] = '*';
                    nr = c-1;
                }
            }
        }

        return ans;
    }
};