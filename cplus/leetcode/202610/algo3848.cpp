#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isDigitorialPermutation(int n) {
        vector<int> p(10, 1);
        for (int i= 2; i<10; i++) p[i] = p[i-1] * i;

        auto x = n; int val = 0;
        while (x) {
            val += p[x % 10];
            x /= 10;
        }
        auto sx = to_string(val), sn = to_string(n); 
        sort(sx.begin(), sx.end()); sort(sn.begin(), sn.end());

        return sx == sn;
    }
};