#include <bits/stdc++.h>
using namespace std;

// 位运算 - 拆位 / 贡献法
class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        // n = nums.size()
        // 对于每一位 one_cnt + zero_cnt = n, 1 可以取奇数个，而 0 可以取任意个，
        // 所有组合数为 1 取奇数个, 0 取任意个. 
        // 其中one_cnt 取奇数个的组合数为 2 ^ (one_cnt-1). 证明 (a+b)^n, a = 1, b = -1
        // 因此每位上的组合数为 2 ^ (one_cnt-1) * 2 ^ (zero_cnt)
        // 合并两项得出 = 2 ^( n-1) 当 one_cnt >= 1 时
        //                0         当 one_cnt =  0 时
        int sum_or = 0;
        for (auto& num: nums) sum_or |= num;
        return sum_or << (nums.size()-1);           // nums.size() 很大时, % (1e9 + 7)
    }
};