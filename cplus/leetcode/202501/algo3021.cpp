#include <bits/stdc++.h>
using namespace std;

// 周赛 382
class Solution {
public:
    long long flowerGame(int n, int m) {
        // 自行解答 枚举 x + y 必须奇数
        long long ans; 
        for (int i=1; i<=n; i++) {
            if (i%2 == 1) ans += m / 2; // 偶数数量 
            else ans += (m+1)/2; // 奇数数量
        }
        return ans;
    }
};