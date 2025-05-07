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

    int firstDayBeenInAllRooms2(vector<int>& nextVisit) {
        // 自行解答，前缀和
        const int mod = 1e9 + 7;
        int ans = 0, cur=0, n = nextVisit.size(), left = n;
        vector<int> cnt(n), pres(n+1);
        for (int i=0; i<n; ++i) {
            if (i == n-1) break;    // 到达最后一个房间
            cnt[i] += 1;            // 达到新房间，数量+1
            pres[i+1] = ((long)pres[i] + cnt[i]) % mod; // 计算前缀和
            if (cnt[i] % 2) {
                // nextVisit[i] 回到 i 需要的天数
                cnt[i] += ((long)pres[i+1] - pres[nextVisit[i]] + mod) % mod; 
                pres[i+1] = ((long)pres[i] + cnt[i]) % mod; // 更新前缀和
            } 
            
        }
        return pres[n-1] % mod;
    } 

    int firstDayBeenInAllRooms3(vector<int>& nextVisit) {
        // 基于 firstDayBeenInAllRooms2 优化
        const int mod = 1e9 + 7;
        int ans = 0, cur=0, n = nextVisit.size(), left = n;
        vector<int> cnt(n), pres(n+1);
        for (int i=0; i<n; ++i) {
            if (i == n-1) break;    // 到达最后一个房间
            // 根据 firstDayBeenInAllRooms2 合并冗余代码
            // 2 表示至少两次从 i-1 -> i, nextVisit[i] 到 i - 1 的天数
            // + mod 避免负数
            cnt[i] = (2 + (long)pres[i] - pres[nextVisit[i]] + mod) % mod;
            pres[i+1] = (pres[i] + cnt[i]) % mod;   // 更新前缀和
            
        }
        // 天数从 0 开始，正好是0 到 n-2 房间的前缀和数量
        return pres[n-1] % mod;
    }    
};