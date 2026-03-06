#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution {
public:
    long long minMoves(vector<int>& balance) {
        // 自行解答
        long long ans = 0, tot = 0; int left, idx = -1, step = 1, n = balance.size();
        for (int i=0; i<n; i++) {
            tot += balance[i]; 
            if (balance[i] < 0) {
                idx = i; left = - balance[i];
            }
        }
        if (tot < 0) return -1;     // 和为负数，无法全为非负数
        if (idx == -1) return 0;    // idx == -1，未找到负数，不需要移位
        while (left) {
            int l = (idx - step + n) % n, r = (idx + step) % n;
            ans += 1LL * min(left, balance[l] + balance[r]) * step;
            step ++; left -= min(left, balance[l] + balance[r]);
        }
        return ans;
    }
};