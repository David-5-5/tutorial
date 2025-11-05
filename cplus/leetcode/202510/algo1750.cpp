#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    int minimumLength(string s) {
        // 自行解答
        int n = s.length(), l = 0, r = n-1;
        while (l < r) {
            if (s[l] != s[r]) break;
            while (l+1<=r && s[l]==s[l+1]) l++;
            while (r-1>=l && s[r]==s[r-1]) r--;
            l ++, r--;
        }

        return max(0, r - l + 1);
    }
};