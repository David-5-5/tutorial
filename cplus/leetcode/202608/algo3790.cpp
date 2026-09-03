#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAllOneMultiple(int k) {
        unordered_set<int> rems;
        int rem = 0, ans = 0;
        while (true) {
            rem = (rem * 10 + 1) % k; ans ++;
            if (rem == 0) return ans;
            if (!rems.insert(rem).second) return -1;
        }

        return -1;
    }
};