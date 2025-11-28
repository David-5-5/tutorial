#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        // 自行解答，理解题目后，实质很简单
        int ones = 0;
        for (auto& ch: s) if(ch=='1') ones += 1;

        int left = 0;
        int ans = ones, i = 0, n = s.length();
        while (i < n) {
            int start = i;
            i ++;
            while (i<n && s[i-1]==s[i]) i++;
            if (s[start] == '0') {
                if (left) ans = max(ans, left + i - start + ones);
                left = i - start;
            }
        }   
        return ans;
    }
};