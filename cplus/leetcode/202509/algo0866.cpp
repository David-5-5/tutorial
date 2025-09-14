#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.1 判断质数
class Solution {
public:
    int primePalindrome(int n) {
        // 自行解答
        auto isprime = [] (long long val) -> bool {
            for (long long i=2; i*i<=val; ++i) {
                if (val % i == 0) return false;
            }
            return val>=2;
        };

        if (n < 10) for (int i=n; i<10; ++i) if (isprime(i)) return i;

        auto str_n = to_string(n); int begin = 1;
        if (str_n.length()/2) begin = stoi(str_n.substr(0, str_n.length()/2)); int end = 1;
        for (int _=0; _<str_n.length()/2; _++) end *= 10;

        while (true) {
            for (int i=begin; i<end; ++i) {
                string suffix = to_string(i); reverse(suffix.begin(), suffix.end());
                int val = stoi(to_string(i) + suffix);
                if (isprime(val) && val>=n) return val;
            }

            for (int i=end/10; i<end; ++i) {
                string suffix = to_string(i); reverse(suffix.begin(), suffix.end());
                for (char mid='0'; mid<='9'; ++mid) {
                    int val = stoi(to_string(i) + mid + suffix);
                    if (isprime(val) && val>=n) return val;
                }
            }
            begin = end; end *= 10;
        }
        return 0;
    }
};