#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.7 交换论证法
class Solution {
public:
    int maxGoodNumber(vector<int>& nums) {
        // 自行解答 - 错误 __builtin_popcount 统计 v 中 1 的 个数
        sort(nums.begin(), nums.end(), [](const int & a, const int & b) {
            int a_bit = __builtin_popcount(a), b_bit = __builtin_popcount(b);
            return ((a << b_bit) | b) > ((b << a_bit) | a);
        });

        int val = 0;
        for (auto v: nums) {
            int bits = __builtin_popcount(v);
            val = (val << bits) | v;
        }
        return val;
    }


};