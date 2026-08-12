#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        map<int, int> cnt;
        for (auto v: arr) cnt[v] ++;

        for (auto [v, c] : cnt) {
            if (c == 0) continue;
            if (v < 0) {
                cnt[v] -= c;
                cnt[v/2] -= c;
                if (v % 2 != 0 || cnt[v/2] < 0) return false;
            } else if (v > 0){
                cnt[v] -= c;
                cnt[v * 2] -= c;
                if (cnt[v*2] < 0) return false;
            } else {
                if (c % 2) return false;
            }
        }
        return true;
    }
};