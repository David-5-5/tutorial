#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumSumOfHeights(vector<int>& heights) {
        long long sum = accumulate(heights.begin(), heights.end(), 0LL), ans = 0;
        int n = heights.size();

        // 枚举顶点
        for (int i=0; i<n; i++) {
            auto l = i-1, r = i + 1; long long sub = 0;
            auto r_val = heights[i], l_val = heights[i];
            while (l>=0) {
                if (heights[l] > r_val) sub += heights[l] - r_val;
                else r_val = heights[l];
                l --;
            }
            while (r < n) {
                if (heights[r] > l_val) sub += heights[r] - l_val;
                else l_val = heights[r];
                r ++;
            }

            ans = max(ans, sum - sub);
        }
        return ans;
    }
};