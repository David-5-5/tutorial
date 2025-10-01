#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.6 最大公约数（GCD）
class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        // 自行解答，裴蜀定理  reduce + gcd 一句话搞定
        return reduce(nums.begin(), nums.end(), 0, [](int a, int b) {
            return gcd(a, b);
        }) == 1;
    }
};