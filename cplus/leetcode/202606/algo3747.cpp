#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countDistinct(long long n) {
        // 组合数学 自行解答
        string s = to_string(n);
        long long ans = (pow(9, s.size()) -9 ) / 8;

        for (int i=0; i<s.length(); i++) {
            auto d = s[i] - '0';
            if (d == 0) break;
            if (i == s.length() - 1) ans += d;
            else ans += (d-1) * pow(9, s.length()-i-1);
        }

        return ans;
    }
};