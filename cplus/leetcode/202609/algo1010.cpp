#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        unordered_map<int, int> cnt; int ans = 0;
        for (auto & t : time) {
            auto s = 60 - t;
            while (s <= 500) {
                if (cnt.count(s)) ans += cnt[s];
                s += 60;
            }
            cnt[t] += 1;
        }
        return ans;
    }
};