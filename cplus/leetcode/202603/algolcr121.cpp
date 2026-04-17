#include <bits/stdc++.h>
using namespace std;

// LCR series 同会员题 240
class Solution {
public:
    bool findTargetIn2DPlants(vector<vector<int>>& plants, int target) {
        deque<pair<int, int>> q; 
        int n = plants.size(); if (n==0)return false;
        int m = plants[0].size(); if (m == 0) return false;
        vector vis(n, vector<bool>(m));

        q.push_back({0, 0}); 
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop_front();
            vis[x][y] = true;
            if (plants[x][y] == target) return true;
            if (plants[x][y] > target) continue;
            if (x+1<n && !vis[x+1][y]) {q.push_back({x+1, y});}
            if (y+1<m && !vis[x][y+1]) {q.push_back({x, y+1});}
        }

        return false;     
    }

    bool findTargetIn2DPlants2(vector<vector<int>>& plants, int target) {
        deque<pair<int, int>> q; 
        int n = plants.size(); if (n==0)return false;
        int m = plants[0].size(); if (m == 0) return false;
        
        int i = 0, j = m - 1;
        while (i<n && j>=0) {
            if (plants[i][j] == target) return true;
            if (plants[i][j] > target) j--;
            else i ++;
        }

        return false; 
    }
};    
