#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.5 因子
class Solution {
public:
    vector<int> closestDivisors(int num) {
        // 自行解答
        int v1 = 1, v2 = num+1, diff = num;
        vector<int> nums = {num+1, num+2};
        
        for (const auto & v: nums) {
            for (int i=2; i*i<=v; ++i) if (v%i == 0) {
                if (i*i == v) return {i, i};
                if (v/i - i < diff) {
                    v1 = i, v2 = v/i; diff = v2 - v1;
                }
            }
        }

        return {v1, v2};     
    }
};