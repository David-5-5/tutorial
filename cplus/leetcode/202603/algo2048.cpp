#include <bits/stdc++.h>
using namespace std;

// 三、字符串贪心 - 3.1 字典序最小/最大 倒序贪心
class Solution {
public:
    int nextBeautifulNumber(int n) {
        // 暴力枚举
        while (true) {
            n ++;
            int cnt[10] {};
            for (int x = n; x > 0; x /= 10) {
                cnt[x%10] ++;
            }
            bool found = true;
            // 出现的数字不需要额外枚举
            for (int x = n; x > 0; x /= 10) {   // 自身出现的数字 cnt[x] == x
                if (cnt[x % 10] != x % 10) {
                    found = false;
                    break;
                }
            }
            if (found) return n;
        }
    }
};