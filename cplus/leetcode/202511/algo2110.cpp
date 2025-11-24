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

    long long getDescentPeriods(vector<int>& prices) {
        // 自行解答 - 分组循环 - 高效
        long long ans = 0; int i = 0, n = prices.size();
        while(i < n) {
            int j = i+1;
            while (j<n && prices[j-1]-1 == prices[j]) j++;
            ans += 1LL * (j-i+1) * (j-i)/2;
            i = j;
        }
        return ans;
    }
    
};