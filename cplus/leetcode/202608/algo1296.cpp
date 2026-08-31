#include <bits/stdc++.h>
using namespace std;

// 同 846
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.size() % k) return false;

        map<int, int> cnt;
        for (auto v : nums) cnt[v] ++;
        for (auto [val, c]: cnt) {
            if (c == 0) continue;
            for (int i=val; i<val+k; i++) {
                if (cnt[i] < c) return false;
                cnt[i] -= c;
            }
        }

        return true;
    }
};