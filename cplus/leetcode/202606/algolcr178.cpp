#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    int trainingPlan(vector<int>& actions) {
        unordered_map<int, int> cnt;
        for (auto& v: actions) cnt[v] ++;

        for (auto& [k, v]: cnt) if (v == 1) return k;

        return 0;
    }
};