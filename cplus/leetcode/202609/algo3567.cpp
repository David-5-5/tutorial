#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n =  grid[0].size();
        if (k == 1) return vector(m-k+1, vector<int>(n-k+1, 0));

        vector ans(m-k+1, vector<int>(n-k+1, 0));
        
        for (int i=0; i<=m-k; i++) {
            vector<int> sub;
            for (int r=0; r<k; r++) for (int c=0; c<k; c++){
                auto it = upper_bound(sub.begin(), sub.end(), grid[i+r][c]);
                sub.insert(it, grid[r+i][c]);
            }
            int res = INT_MAX;
            for (int x=1; x<k*k; x++) if (sub[x] > sub[x-1]) {
                res = min(res, sub[x]-sub[x-1]);
            }
            if (res < INT_MAX) ans[i][0] = res;
            // 更新每列
            for (int j=1; j<=n-k; j++) {
                
                for (int r=0; r<k; r++) {
                    auto it = lower_bound(sub.begin(), sub.end(), grid[r+i][j-1]);
                    sub.erase(it);
                    it = upper_bound(sub.begin(), sub.end(), grid[r+i][j+k-1]);
                    sub.insert(it, grid[r+i][j+k-1]);
                }
                int res = INT_MAX;
                for (int x=1; x<k*k; x++) if (sub[x] > sub[x-1])  {
                    res = min(res, sub[x]-sub[x-1]);
                }       
                if (res < INT_MAX) ans[i][j] = res;         
            }
        }
        return ans;
    }
};