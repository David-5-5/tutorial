#include <bits/stdc++.h>
using namespace std;

// 同 121
class Solution {
public:
    int bestTiming(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        
        int ans = 0, mn = prices[0];
        for (int i=1; i<prices.size(); i++) {
            ans = max(ans, prices[i] - mn);
            mn = min(mn, prices[i]);
        }
        return ans;     
    }
};