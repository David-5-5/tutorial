#include <bits/stdc++.h>
using namespace std;

// 位运算 - 拆位 / 贡献法
class Solution {
public:
    long long sumDigitDifferences(vector<int>& nums) {
        int bit_len = to_string(nums[0]).length(), n = nums.size();
        long long ans = 0;

        for (int _=0; _<bit_len; ++_) {
            unordered_map<int, int> bit_cnt;
            for (int j=0; j<n; ++j) {
                int k = nums[j] % 10; nums[j] /= 10;
                bit_cnt[k] ++;
            }
            for (auto& [_, v]:bit_cnt) ans += (long) v * (n - v);
        }
        return ans / 2;   
    }
};