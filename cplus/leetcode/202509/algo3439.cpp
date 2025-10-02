#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        // 自行解答。这个边界条件太费事了
        int ans = 0;
        int n = startTime.size();
        int pres = 0; for (int i=0; i<k&&i<n; ++i) pres += endTime[i] - startTime[i];
        if (k >= n) return eventTime - pres;
        for (int i=k; i<n; ++i) {
            ans = max(ans, startTime[i] - pres - (i>k?endTime[i-k-1]:0));   // 才开始将k写成1
            pres += (endTime[i]-startTime[i]) - (endTime[i-k]-startTime[i-k]);
        }

        ans = max(ans, eventTime - pres - endTime[n-k-1]);  // 将最后一个会议前移
        return ans;   
    }
};