#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.4 子集状压 DP
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> cnt;
        for (auto& v : nums) cnt[v] ++;
        vector<int> ini;
        for (auto& [_, v]: cnt) ini.push_back(v);        

        int  n = cnt.size(), m = 1 << quantity.size();
        for (int mask=0; mask<m; ++mask) {
            
        }



        for (auto& v: dp[(1<<n)-1]) if (v>=0) return true;
        return false;

    }
};