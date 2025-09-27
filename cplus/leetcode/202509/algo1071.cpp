#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.6 最大公约数（GCD）
class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        // 最大公约数的字符串一定是其最大的相同前缀字符串
        int len = gcd(str1.length(), str2.length());

        auto check = [&](string str, string pre) -> bool {
            for (int i=0; i<str.length(); i++) {
                if (str[i] != pre[i%len]) return false;
            }

            return true;
        };

        auto prefix = str1.substr(0, len);
        if (check(str1, prefix) && check(str2, prefix)) return prefix;
        else return "";
    }


};