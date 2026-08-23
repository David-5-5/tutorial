#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool sumGame(string num) {
        int sl = 0, sr = 0, ql=0, qr = 0, n = num.length() / 2;
        for (int i=0; i<n; i++) {
            if (num[i] == '?') ql ++;
            else sl += num[i] - '0';
            if (num[i+n] == '?') qr ++;
            else sr += num[n+i] - '0';
        }

        return (ql + qr) % 2 || sr - sl == (ql - qr) * 9 / 2;
    }
};