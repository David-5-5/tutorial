#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        // 非暴力做法，O(NlogN) 滑动窗口 + 有序列表
        multiset<int> windows; int n = nums.size();  vector<int> pres(n + 1);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + nums[i];
        int ans = INT_MAX;

        for (int i=l; i<=n; i++) {
            windows.insert(pres[i-l]);
            auto it = windows.lower_bound(pres[i]);
            if (it != windows.begin()) {
                ans = min(ans, pres[i] - *prev(it));
            }

            if (i >= r) {
                auto it = windows.lower_bound(pres[i-r]); windows.erase(it);
            }
        }
        return ans == INT_MAX? -1 : ans; 

    }
};