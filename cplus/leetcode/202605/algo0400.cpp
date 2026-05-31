#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    int findNthDigit(int n) {
        int start = 1, width = 1;
        while (n > 9LL * start  * width) {
            n -= start * 9 * width;
            start *= 10; width ++;
        }
        auto val = start + (n-1) / width, rem = (n-1) % width;
        return stoi(to_string(val).substr(rem, 1));        
    }
};