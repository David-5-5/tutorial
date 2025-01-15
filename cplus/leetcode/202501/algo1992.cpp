#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 脑筋急转弯
class Solution {
public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        // 自行解答，有些繁琐
        int n = land.size(), m = land[0].size();
        vector<vector<bool>> vis;
        vis.assign(n, vector<bool>(m));

        
        auto find = [&](int r, int c) -> vector<int> {
            vector<int> farm = {r,c};            
            int x = r, y = c;
            while (x+1<n && land[x+1][y]==1) x++;
            while (y+1<m && land[x][y+1]==1) y++;
            farm.push_back(x), farm.push_back(y);
            for (int i=r; i<=x; i++) 
                for (int j=c; j<=y; j++)
                    vis[i][j] = true;
            return farm;
        };

        vector<vector<int>> ans;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (!vis[i][j] && land[i][j]) ans.push_back(find(i,j));
            }
        }

        return ans;   
    }
};