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

    vector<vector<int>> findFarmland2(vector<vector<int>>& land) {
        // 不需要 vis 数组，判断land[i][j] 的 左 和 上 是否为 1
        int n = land.size(), m = land[0].size();
        
        auto find = [&](int r, int c) -> vector<int> {
            vector<int> farm = {r,c};            
            int x = r, y = c;
            while (x+1<n && land[x+1][y]==1) x++;
            while (y+1<m && land[x][y+1]==1) y++;
            farm.push_back(x), farm.push_back(y);
            return farm;
        };

        vector<vector<int>> ans;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) 
                if (land[i][j]) {
                    if (i>0 && land[i-1][j]==1 || j>0 && land[i][j-1] ==1) 
                        continue; // 矩形内部
                    ans.push_back(find(i,j));
                }
        }

        return ans;
    }
};