#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int countHomogenous(string s) {
        // 自行解答，使用 分组循环模板
        const int mod = 1e9 + 7;
        long long ans = 0; int i = 0, n = s.length();
        while (i < n) {
            int j = i + 1;
            while (s[j] == s[i]) j++;
            ans += 1LL * (j-i+1) * (j - i)/2;
            i = j;
        }
        return ans % mod;
    }
};