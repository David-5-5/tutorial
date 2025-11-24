#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int longestContinuousSubstring(string s) {
        // 自行解答
        int i = 0, ans = 1, n = s.length();
        while (i < n) {
            // 无 i+1<n 也能通过，测试案例覆盖不全面
            for (int j=1; i+1<n && j<26; ++j) {
                if (s[i]+1 == s[i+1]) {
                    ans = max(ans, j+1); i++;
                } else break;
            }
            i++;
        }
        return ans;  
    }
};