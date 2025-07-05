#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  一维 DP
class Solution {
public:
    int racecar(int target) {
        int n = 1, step = 1;
        while (n <= target) n <<= 1;
        vector<int> dp(n, INT_MAX);

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> que;

        dp[0] = 0;
        while ((1<<step) - 1 < n) {
            que.emplace(step, (1<<step)-1, 1);
            step ++;
        }

        auto nxt = [](int pos, int dir, int step) -> int{
            return pos + dir * ((1<<step)-1);
        };

        auto check = [&] (int pos, int dir, int step) -> bool{
            int new_pos = nxt(pos, dir, step);
            return new_pos >0 && new_pos < n;
        };

        while (!que.empty()) {
            auto [val, pos, dir] = que.top(); que.pop();
            if (pos == target) return val;
            if (val > dp[pos]) continue; // 剪枝，否则超时
            else dp[pos] = val;          // 关键，出队列时，设置值
            // 同方向继续 AA， + 2 
            step = 1;
            while (check(pos, dir, step)) {
                int nxtPos = nxt(pos, dir, step);
                if (dp[nxtPos] > val + 2 + step) {
                    que.emplace(val + 2 + step, nxtPos, dir);
                }
                step += 1;
            }
            // 反方向继续 A， + 1 
            step = 1;
            while (check(pos, dir*-1, step)) {
                int nxtPos = nxt(pos, dir*-1, step);
                if (dp[nxtPos] > val + 1 + step) {
                    que.emplace(val + 1 + step, nxtPos, dir*-1);
                }
                step += 1;
            }
        }

        return -1;     
    }
};
