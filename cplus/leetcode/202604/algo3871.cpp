#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.5 贡献法
class Solution {
public:
    long long countCommas(long long n) {
        string str_n = to_string(n); int len = str_n.length();

        long long ans = 0;
        for (int i = 4; i<len; i++) {
            ans += 9LL * ((i-1)/3) * pow(10, i-1);
        }
        ans += 1LL * ((len-1)/3) * (n - pow(10, len-1) + 1);

        return ans;
    }
};