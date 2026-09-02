#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countElements(vector<int>& nums, int k) {
        map<int, int, greater<int>> cnt;
        for (auto v: nums) cnt[v] ++;
        
        int gr_cnt = 0, ans = 0;
        for (auto [_, v]: cnt) {
            if (gr_cnt >= k) ans += v;
            gr_cnt += v;
        }
        return ans;
    }

  
};