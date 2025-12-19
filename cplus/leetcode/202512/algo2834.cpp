#include <bits/stdc++.h>
using namespace std;

// 数学算法 7.7 其他
class Solution {
public:
    int minimumPossibleSum(int n, int target) {
        // 自行解答 同 2829
        const int mod = 1e9 + 7;
        int h = min(n,target/2);
        int ans = ((1LL + h) * h/ 2) % mod;
        if (n > h) ans = (1LL * ans + (1LL * target*2+n-h-1)% mod * (n-h) /2) % mod ;

        return ans;         
    }
};