#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minimumDistance(string word) {
        // Pos of alphabet in matrix
        int pos[26][2] = {{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},
                          {1,0},{1,1},{1,2},{1,3},{1,4},{1,5},
                          {2,0},{2,1},{2,2},{2,3},{2,4},{2,5},
                          {3,0},{3,1},{3,2},{3,3},{3,4},{3,5},
                          {4,0},{4,1}};

        auto dis = [&](int x, int y) -> int {
            if (x == 26 || y == 26) return 0;
            return abs(pos[x][0]-pos[y][0]) + abs(pos[x][1]-pos[y][1]);
        };

        int n = word.size();
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(27, vector<int>(27, -1)));
        auto dfs = [&](this auto&& dfs, int i, int p, int q) -> int {
            if (i < 0) return 0;
            
            auto& res = memo[i][p][q];
            if (res != -1) return res;

            int t = word[i] - 'A';
            return res = min(dfs(i-1, t, q)+dis(p, t), dfs(i-1, p, t)+dis(q, t));
        };

        return dfs(n-1, 26, 26);
    }
};