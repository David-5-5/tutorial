#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 脑筋急转弯
class Solution {
public:
    int countCollisions(string directions) {
        // 自行解答，分类讨论
        int l = 0, r = 0, s = 0, ans = 0;
        for (auto ch : directions) {
            if (ch == 'S') {
                ans += r;
                r = 0;
                s = 1;
            } else if (ch == 'L') {
                if (r > 0) {
                    ans += 2, r--; // 变成 s
                    // 同 s
                    ans += r;
                    r = 0;
                    s = 1;
                } else if (s > 0) {
                    ans += 1;
                } else l += 1;

            } else {
                r += 1;
            }
        }

        return ans;
    }
};