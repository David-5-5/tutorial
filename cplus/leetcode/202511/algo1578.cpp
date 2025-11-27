#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        // 自行解答，使用 分组循环模板
        int ans = 0, i = 0, n = colors.length();
        while (i < n) {
            int j = i, pres = 0, mx = 0;
            while (j < n && colors[j] == colors[i]) {
                pres += neededTime[j]; mx = max(mx, neededTime[j]); j++;
            }
            ans += pres - mx;
            i = j;
        }
        return ans;
    }
};