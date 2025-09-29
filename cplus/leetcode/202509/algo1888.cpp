#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    int minFlips(string s) {
        // 参考题解， 并未实现，打心里特别厌恶这样的题目，没有意义，为啥操作1不计数，操作2要计数
        int n = s.size(), ans = n, cnt = 0;
        for (int i = 0; i < n * 2 - 1; i++) {
            cnt += (s[i % n] ^ i) & 1;
            int left = i - n + 1;
            if (left < 0) {
                continue;
            }
            ans = min({ans, cnt, n - cnt});
            cnt -= (s[left] ^ left) & 1;
        }
        return ans;

    }
};