#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.4 逆向思维
class Solution {
public:
    char processStr(string s, long long k) {
        // 自行解答
        long long n = 0;
        for (auto ch : s) {
            if (ch == '*' && n) n --;       // n 不能为负数
            else if (ch == '#') n *= 2;
            else if (ch >= 'a' && ch <= 'z') n += 1;
        }

        if (k >= n) return '.'; // k 最大是 n - 1

        reverse(s.begin(), s.end());
        for (auto ch : s) {
            if (ch == '*') n ++;
            else if (ch == '#') {
                n /= 2; if (k >= n) k -= n;
            } else if (ch >= 'a' && ch <= 'z') {                
                n -= 1;
                if (k == n) return ch;
            } else { // % 
                k = n - k - 1;  // reverse
            }
        }
        return '.';
    }
};