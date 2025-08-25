#include <bits/stdc++.h>
using namespace std;

// 位运算 - 拆位 / 贡献法
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        // 自行解答
        int ans = 0; vector<int> bit_cnt(32); int n = nums.size();
        for (auto num: nums) for (int i = 0; i<32; ++i) {
            if ((num >> i) & 1) bit_cnt[i] ++;
        }
        for (int i = 0; i<32; ++i) ans += bit_cnt[i] * (n-bit_cnt[i]);

        return ans;
    }
};