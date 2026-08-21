#include <bits/stdc++.h>
using namespace std;

// 同 1296
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize) return false;

        map<int, int> cnt;
        for (auto v : hand) cnt[v] ++;
        for (auto [val, c]: cnt) {
            if (c == 0) continue;
            for (int i=val; i<val+groupSize; i++) {
                if (cnt[i] < c) return false;
                cnt[i] -= c;
            }
        }

        return true;        
    }
};