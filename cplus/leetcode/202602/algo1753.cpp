#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.8 相邻不同
class Solution {
public:
    int maximumScore(int a, int b, int c) {
        // 自行解答 题单说明的问题 2 min(floor((a + b + c)/2), a+b+c - max(a,b,c))
        return min((a + b + c)/2, (a + b + c) - max({a,b,c}));
    }
};