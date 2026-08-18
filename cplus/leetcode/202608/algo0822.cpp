#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        int ans = INT_MAX, n = fronts.size();
        set<int> forbid;
        for (int i=0; i<n; i++) if (fronts[i] == backs[i]) 
            forbid.insert(fronts[i]);
        for (int i=0; i<n; i++) if (fronts[i] != backs[i]) {
            if (!forbid.count(fronts[i])) ans = min(ans, fronts[i]);
            if (!forbid.count(backs[i])) ans = min(ans, backs[i]);
        }
        return ans == INT_MAX? 0 : ans;
    }
};