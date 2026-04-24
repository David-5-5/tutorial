#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.6 两次扫描
class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        // 自行解答，难度分 2374 基础 3796
        restrictions.push_back({1, 0});
        sort(restrictions.begin(), restrictions.end());

        int m = restrictions.size();
        for (int i=1; i<m; ++i) {
            auto & l_idx = restrictions[i-1][0], & l_h = restrictions[i-1][1], 
                & r_idx = restrictions[i][0], &r_h = restrictions[i][1]; 
            r_h = min(r_h, l_h + r_idx - l_idx);
        }
        int ans = restrictions[m-1][1] + n - restrictions[m-1][0];
        for (int i=m-1; i; --i) {
            auto & r_idx = restrictions[i][0], &r_h = restrictions[i][1], 
                & l_idx = restrictions[i-1][0], &l_h = restrictions[i-1][1]; 
            l_h = min(l_h, r_h + r_idx - l_idx);

            ans = max(ans, max(l_h, r_h) + ((r_idx - l_idx) - abs(l_h-r_h)) / 2);
        }
        
        return ans;
    }
};