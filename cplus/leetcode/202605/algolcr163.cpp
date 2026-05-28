#include <bits/stdc++.h>
using namespace std;

// LCR series 同 400
class Solution {
public:
    int findKthNumber(int k) {
        // 自行解答
        if (k == 0) return 0;

        int start = 1, width = 1;
        while (k > 9LL * start  * width) {
            k -= start * 9 * width;
            start *= 10; width ++;
        }
        auto val = start + (k-1) / width, rem = (k-1) % width;
        return stoi(to_string(val).substr(rem, 1));             
    }
};