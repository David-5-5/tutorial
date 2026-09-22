#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        set<pair<int, int>> comms;
        int m = grid.size(), n = grid[0].size();
        
        for (int r=0; r<m; r++) {
            vector<int> cols;
            for (int c=0; c<n; c++) {
                if (grid[r][c]) cols.emplace_back(c);
            }
            if (cols.size() > 1) 
                for (auto & c :cols) comms.emplace(r, c);
        } 
        for (int c=0; c<n; c++) {
            vector<int> rows;
            for (int r=0; r<m; r++) {
                if (grid[r][c]) rows.emplace_back(r);
            }
            if (rows.size() > 1) 
                for (auto & r :rows) comms.emplace(r, c);
        } 

        return comms.size();
    }

};