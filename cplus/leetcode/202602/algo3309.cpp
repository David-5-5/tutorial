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

    int maxGoodNumber2(vector<int>& nums) {
        // 参考题解 __lg vs __builtin_popcount
        sort(nums.begin(), nums.end(), [](const int & a, const int & b) {
            int a_bit = __lg(a) + 1, b_bit = __lg(b) + 1;
            return ((a << b_bit) | b) > ((b << a_bit) | a);
        });

        int val = 0;
        for (auto v: nums) {
            int bits = __lg(v) + 1;
            val = (val << bits) | v;
        }
        return val;   
    }
};