#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int minLengthAfterRemovals(string s) {
        int cnt_a = 0, cnt_b = 0;
        for (auto & ch : s) if ( ch == 'a') cnt_a ++; else cnt_b ++;

        return abs(cnt_a - cnt_b);
    }
};