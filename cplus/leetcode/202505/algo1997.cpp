#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.1 前缀和优化 DP
class Solution {
public:
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        // 自行解答，朴素算法，超时
        const int mod = 1e9 + 7;
        int ans = 0, cur=0, n = nextVisit.size(), left = n;
        vector<int> cnt(n);
        while (left) {
            if (cnt[cur] == 0) left --;
            cnt[cur]++;
            if (cnt[cur] % 2) {
                cur = nextVisit[cur];
            } else cur = (cur + 1) % n;
            ans ++;
        }
        return ans % mod;
    }
};