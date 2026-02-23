#include <bits/stdc++.h>
using namespace std;

// 同 539
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        // 自行解答
        const int mod = 24 * 60;
        int ans = mod, n = timePoints.size();

        auto to_min = [] (string t) -> int {
            return stoi(t.substr(0,2)) * 60 + stoi(t.substr(3,2));
        };

        sort(timePoints.begin(), timePoints.end());
        ans = (mod + to_min(timePoints[0]) - to_min(timePoints[n-1])) % mod;

        for (int i=1; i<n; ++i) {
            ans = min(ans, to_min(timePoints[i]) - to_min(timePoints[i-1]));
        }

        return ans;
        
    }
};