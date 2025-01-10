#include <bits/stdc++.h>
using namespace std;

// 双周赛 3301
class Solution {
public:
    long long maximumTotalSum(vector<int>& maximumHeight) {
        sort(maximumHeight.begin(), maximumHeight.end());
        reverse(maximumHeight.begin(), maximumHeight.end());
        long long ans = 0;
        int avail = INT_MAX;
        for (auto h : maximumHeight){
            if (avail <=0) return -1;
            if (avail >= h) ans += h;
            else ans += avail;

            avail = min(avail, h) - 1;
        }
        
        return ans;   
    }
};