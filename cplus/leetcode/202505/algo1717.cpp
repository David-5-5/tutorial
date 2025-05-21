#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.3 邻项消除
class Solution {
public:
    int maximumGain(string s, int x, int y) {
        // 自行解答，用栈的思路，不需要栈
        // 优先合并值大的组合
        int a_cnt = 0, b_cnt = 0, ans = 0;

        s += 'c'; // 哨兵
        for (auto& ch : s) {
            if (ch != 'a' && ch != 'b') {
                // 剩下的 a b 也两两合并，一定是比较小的值
                ans += min(x, y) * min(a_cnt, b_cnt);
                a_cnt = 0, b_cnt = 0;
            } else if (ch == 'a') {
                if (y > x && b_cnt) {
                    ans += y, b_cnt --;
                } else a_cnt ++;
            } else {
                if (y > x || !a_cnt) {
                    b_cnt ++;
                } else {
                    ans += x, a_cnt --;
                }
            }
        }

        return ans;

    }
};