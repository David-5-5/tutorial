#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        // 前后缀分解，每个元素前后的最大空隙
        int n = startTime.size();
        int ans = max(startTime[1]-(endTime[0]-startTime[0]),       // 将 i = 0 会议移动 0 开始
            eventTime-endTime[n-2]-(endTime[n-1]-startTime[n-1]));  // 将 i = n-1 会议移动 eventTime 结束
        
        vector<int> suf_mx(n); suf_mx[n-1] = eventTime - endTime[n-1];
        for (int i=n-2; i; --i) {
            suf_mx[i] = max(suf_mx[i+1], startTime[i+1] - endTime[i]);
        }

        if (suf_mx[1] >= endTime[0] - startTime[0])
            ans = max(ans, startTime[1]);   // 将 i=0 会议 移动 会议 1 之后安排
        int pre_mx = startTime[0];
        // 因此枚举 i 会议， i-1 与 i + 1 之间的最大值
        // 1： i-1 与 i + 1的空余 - i会议时长
        // 2： i-1 之前有空余区间大于 i 或 i + 1 之后有空余区间大于 i，则 i-1 与 i+1空余
        for (int i=1; i<n-1; ++i) {
            auto d = endTime[i] - startTime[i];
            ans = max(ans, startTime[i+1] - endTime[i-1] - (d<=pre_mx || d<=suf_mx[i+1]?0:d));
            pre_mx = max(pre_mx, startTime[i] - endTime[i-1]);
        }

        // 将 i=n-1 会议 移动 会议 n-1 之前
        if (pre_mx >= endTime[n-1] - startTime[n-1]) ans = max(ans, eventTime-endTime[n-2]);

        return ans;   
    }
};