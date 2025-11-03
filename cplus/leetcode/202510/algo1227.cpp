#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 概率期望
class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        // 猜的答案，参见题解 动态规划 -> 推导出答案
        return n==1?1.0:0.5;
    }
};