#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution {
public:
    int minimumBuckets(string hamsters) {
        // 自行解答
        int ans = 0, prev = -1, n = hamsters.length();
        hamsters = 'H' + hamsters + 'H';                // 前后加两个仓鼠作为哨兵
        for (int i=1; i<=n; ++i) {
            if (prev == i-1 || hamsters[i] == '.') continue;
            if (hamsters[i-1] == 'H' && hamsters[i+1] == 'H') return -1;
            
            if (hamsters[i+1] == '.') prev = i + 1;     // 优先在后面放置事务痛
            else prev = i - 1;
            ans ++;
        }

        return ans;   
    }
};