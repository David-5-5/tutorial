#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.6 最大公约数（GCD）
class Solution {
public:
    bool canMeasureWater(int x, int y, int target) {
        return x+y>= target && target % gcd(x, y) == 0;
    }
};