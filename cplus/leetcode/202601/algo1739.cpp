#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    int minimumBoxes(int n) {
        // 自行解答 二分
        auto nxt = [&] (int m) -> int {
            int h = ceil((sqrt(8LL * m + 1)-1) / 2);
            return h * (h - 1) / 2 + m - h * (h+1) / 2;
        };

        auto check = [&](int mid) -> bool {
            int res = 0;
            while (mid) {
                if (res >= n) return true;
                res += mid; mid = nxt(mid);
            }
            return res >= n;
        };

        int left = 0, right = n + 1;
        while (left + 1 < right) {
            int m = (left + right) / 2;
            if (check(m))
                right = m;
            else left = m;
        }

        return right;
    }
    
};