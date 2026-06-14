#include <bits/stdc++.h>
using namespace std;

// 贪心 八、其他
class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        // 自行解答，变量太复杂，容易写错
        int ans = INT_MAX, mn_fin_land = INT_MAX, mn_fin_water = INT_MAX;
        int m = landStartTime.size(), n = waterStartTime.size();

        for (int i=0; i<m; i++) {
            auto s = landStartTime[i], d = landDuration[i];
            mn_fin_land = min(mn_fin_land, s + d);
        }

        for (int i=0; i<n; i++) {
            auto s = waterStartTime[i], d = waterDuration[i];
            ans = min(ans, max(mn_fin_land, s) + d);
        }

        for (int i=0; i<n; i++) {
            auto s = waterStartTime[i], d = waterDuration[i];
            mn_fin_water = min(mn_fin_land, s + d);
        }

        for (int i=0; i<m; i++) {
            auto s = landStartTime[i], d = landDuration[i];
            ans = min(ans, max(mn_fin_water, s) + d);
        }

        return ans;
    }

};