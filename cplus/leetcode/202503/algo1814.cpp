#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int countNicePairs(vector<int>& nums) {
        const int mod = 1e9 + 7;

        auto rev = [](int v) -> int {
            int res = 0;
            while (v) {
                res = res * 10 + v % 10;
                v /= 10;
            }
            return res;
        };

        int ans = 0;
        unordered_map<int, int> diff;
        for (auto& v:nums) {
            int d = v - rev(v);
            ans = (ans + diff[d]) % mod;
            diff[d] ++;
        }
        return ans;
    }   
};