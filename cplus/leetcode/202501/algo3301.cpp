#include <bits/stdc++.h>
using namespace std;

// 双周赛 3301
class Solution {
public:
    long long maximumTotalSum(vector<int>& maximumHeight) {
        // 自行解答
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


    long long maximumTotalSum2(vector<int>& maximumHeight) {
        // 参考题解，focus on c++ usage
        ranges::sort(maximumHeight, greater());

        for (int i=1; i<maximumHeight.size(); i++) {
            maximumHeight[i] = min(maximumHeight[i-1]-1, maximumHeight[i]);
            if (maximumHeight[i] <= 0) return -1;
        }
        
        return reduce(maximumHeight.begin(), maximumHeight.end(), 0LL);   
    }
};