#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        int sign = 1, mx = INT_MAX / 10;
        int state = 0; // 0, 1
        set<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

        int ans = 0;
        for (auto& ch : str) {
            if (state == 0) {
                if (ch == ' ') continue;
                else if (ch == '-' || ch == '+') {
                    state = 1;
                    if (ch == '-')  sign *= -1;
                } else if (digits.count(ch)) {
                    state = 1;
                    ans = ch - '0';
                } else break;
            } else {
                if (digits.count(ch)) {
                    int d = ch - '0';
                    if (ans > mx || (ans == mx && d > 6 && sign == 1) || 
                         (ans == mx && sign == -1 && d > 7 ) )
                        return (sign==1)?INT_MAX:INT_MIN;
                    ans = ans * 10 + d;
                } else break;
            }
        }
        return sign * ans;
    }
};