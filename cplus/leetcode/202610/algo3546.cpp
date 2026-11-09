#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        long long sum = 0; int m = grid.size(), n = grid[0].size();
        for (int i = 0; i<m; i++) for (int j=0; j<n; j++) {
            sum += grid[i][j];
        }
        if (sum % 2) return false;
        
        long long half = 0;
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                half += grid[i][j];
            }
            if (half == sum / 2) return true;
            else if (half > sum / 2) break;
        }
        half = 0;
        for (int j=0; j<n; j++) {
            for (int i=0; i<m; i++) {
                half += grid[i][j];
            }
            if (half == sum / 2) return true;
            else if (half > sum / 2)  break;
        }
        return false;
    }
};