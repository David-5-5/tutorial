#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countWays(vector<int>& nums) {
        map<int, int> cnt; int ans = 0;
        for (auto v: nums) cnt[v] ++;
        
        if (cnt.begin()->first) ans ++; // 全不选
        int selected = 0;
        for (auto it = cnt.begin(); it!=cnt.end(); it++) {
            selected += it->second;
            if (selected > it->first && (next(it) == cnt.end() || selected < next(it)->first)) ans ++;
        }
        return ans;
    }
};