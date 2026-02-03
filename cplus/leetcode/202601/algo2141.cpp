#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        // 参考题解 二分
        long long tot = accumulate(batteries.begin(), batteries.end(), 0LL);
        long long l = 0, r = tot/n + 1;
        while (l+1 < r) {
            long long  mid = (l + r) / 2;
            long long sum = 0;
            for (long long b: batteries) {
                sum += min(b, mid);
            }
            ((sum >= mid * n)? l: r) = mid;
        }

        return l;
    }

    long long maxRunTime2(int n, vector<int>& batteries) {
        // 参考题解 排序 + 贪心
        sort(batteries.rbegin(), batteries.rend());
        long long tot = accumulate(batteries.begin(), batteries.end(), 0LL);
        long long x = tot / n; int m = batteries.size();
        for (int i=0; i<m; ++i) {
            if (batteries[i] <= x) break;
            tot -= batteries[i]; n--;
            x = tot / n;
        }
        return x;   
    }
};