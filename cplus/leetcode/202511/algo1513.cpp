#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int numSub(string s) {
        // 自行解答 可作为 分组循环 的 模板
        const int mod = 1e9 + 7;
        long long ans = 0;
        int i = 0, n = s.length();
        while (i < n) {
            if (s[i] == '1') {
                int j = i;
                while (i<n && s[i] == '1') ans += i-j+1, i++;
            } else i ++;
        }
        return ans % mod;   
    }
};