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

    long long flowerGame(int n, int m) {
        // 自行解答 公式，n偶数数量 * m奇数数量 + n奇数数量 * m偶数数量
        long long n_odd = (n + 1) / 2, m_odd = (m+1) / 2;
        long long n_even = n - n_odd, m_even = m - m_odd;
        return (long long)  n_odd * m_even + n_even * m_odd;
    }
};