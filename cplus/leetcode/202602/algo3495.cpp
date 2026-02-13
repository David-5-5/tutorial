#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.8 相邻不同
class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        auto count = [](int l, int r) -> long long {
            long long mx = r / 4 + 1;
            long long n = r - l + 1;
            int a = (l+3) / 4, b = r/4 - 1;
            n += (a * 4 - l) * (a-1);           // Append begin
            n += (r - (b+1) * 4 + 1) * (b + 1); // Append end
            n += (a + b) * (b-a+1) * 2;         // Append middle
            return max((n + 1)/2, mx);
        };

        long long ans = 0;
        for (auto & q: queries) ans += count(q[0], q[1]);

        return ans;
    }
};