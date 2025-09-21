#include <bits/stdc++.h>
using namespace std;

// 其他递归/分治
class Solution {
public:
    vector<vector<int>> specialGrid(int n) {
        // 自行解答
        int begin = 0;

        vector<vector<int>> ans(1<<n, vector<int>(1<<n));

        auto dfs = [&](this auto&& dfs, int i, int j, int d) -> void {
            if (d == 0) {
                ans[i][j] = begin++;
                return;
            }
            
            auto offset = 1 << (d-1);
            dfs(i, j, d-1);
            dfs(i+offset, j, d-1);
            dfs(i+offset, j-offset, d-1);
            dfs(i, j-offset, d-1);
        };
        
        dfs(0, (1<<n)-1, n);
        return ans;      

    }
};