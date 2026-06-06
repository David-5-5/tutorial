#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    vector<int> sockCollocation(vector<int>& sockets) {
        int x = 0;
        for (auto& s: sockets) x ^= s;

        auto lb = x & (-x); // lowbit 取任意为 1 的位
        vector<int> ans(2);
        for (auto& s: sockets) {
            if (s & lb) ans[0] ^= s;
            else ans[1] ^= s;
        }

        return ans;
    }
};