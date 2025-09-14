#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    int countTriplets(vector<int>& nums) {
        // 参考题解，枚举的方法 非组合数学的方法
        // unordered_map<int, int> cnt; int ans = 0;
        // for (auto& x: nums) for (auto& y:nums) cnt[x&y] ++;
        // for (auto& x: nums) for (auto&[k,v]:cnt) if ((x&k)==0)ans += v;
        // return ans;

        // vector is fast than unordered_map
        vector<int> cnt(1<<16); int ans = 0;
        for (auto& x: nums) for (auto& y:nums) cnt[x&y] ++;
        for (auto& x: nums) for (int k=0; k<(1<<16); ++k) if ((x&k)==0)ans += cnt[k];
        return ans;        
    }

    int countTriplets2(vector<int>& nums) {
        // 参考题解，优化，二进制枚举
        vector<int> cnt(1<<16); int ans = 0;
        for (auto& x: nums) for (auto& y:nums) cnt[x&y] ++;
        for (auto& x: nums) {
            auto mask = x ^ ((1<<16)-1), k = mask;
            while (k) {
                ans += cnt[k]; k = (k-1) & mask;
            }
            ans += cnt[0];
        }
        return ans;
    }
};