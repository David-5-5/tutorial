#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector vis(rows, vector<bool>(cols));
        vector<vector<int>> ans;
        int d = 0; vis[rStart][cStart] = true; ans.push_back({rStart, cStart});
        int x = rStart, y = cStart;

        auto can_turn = [&]() -> bool {
            if (x + dirs[d][0] == -2 || x + dirs[d][0] == rows + 1 ||
                y + dirs[d][1] == -2 || y + dirs[d][1] == cols + 1) return  true;
            auto nd = (d + 1) % 4;
            auto nx = x + dirs[nd][0], ny = y + dirs[nd][1];
            if (nx >= 0 && nx < rows && ny>=0 && ny < cols && vis[nx][ny]) return false;

            return true;
        };

        while (ans.size() < rows * cols) {
            x = x + dirs[d][0], y = y + dirs[d][1];
            if (x >= 0 && x < rows && y>=0 && y < cols) {
                ans.push_back({x, y}); vis[x][y] = true;
            }
            
            if (can_turn()) d = (d + 1) % 4;
        }

        return ans;
    }
};

