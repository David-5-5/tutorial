#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int maximumSum(vector<int>& nums) {
        unordered_map<int, int> mx;

        int ans = -1;
        for (auto& x: nums) {
            int sum = 0, v=x;
            while (v) 
                sum += v % 10, v /= 10;

            if (mx.count(sum)) 
                ans = max(ans, x + mx[sum]);
            mx[sum] = max(mx[sum], x);
        }

        return ans;       

    }
};