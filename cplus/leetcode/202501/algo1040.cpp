#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 等价转换
class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        // 参考题解
        int n = stones.size(), mx = 0, mn = INT_MAX;
        sort(stones.begin(), stones.end());

        // 移动的最大值, 移动左右两个端点，比较剩下两个端点中间的空值
        mx = max(stones[n-1] - stones[1], stones[n-2]-stones[0]) - (n-2);

        // 特殊情况的最小值，一端都是连续的，最小值为 2
        if (stones[n-2]-stones[0] == n-2 || stones[n-1]-stones[1] == n-2)
            return {min(2, mx), mx};
        
        // n 大小的滑动窗口，找滑动窗口里的最大石子数 maxcnt，n - maxcnt 即为最小值
        int maxcnt = 0, l = 0;
        for (int r=0; r < n; r++) {
            while (stones[r] - stones[l] >= n) l++;

            maxcnt = max(maxcnt, r - l + 1);
        }

        return {n - maxcnt, mx};     
    }
};