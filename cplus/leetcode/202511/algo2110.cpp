#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        // 自行解答
        long long ans = 1; int prev = 1, n = prices.size();
        for (int i=1; i<n; ++i) {
            if (prices[i-1] - 1 == prices[i]) prev ++;
            else prev = 1;
            ans += prev;
        }
        return ans;
    }


};