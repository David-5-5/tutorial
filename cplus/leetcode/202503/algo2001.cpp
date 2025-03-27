#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        // 自行解答
        unordered_map<double, long> cnt;
        long ans = 0;
        for (auto& v:rectangles) {
            double ratio = (double) v[0] * 1.0 / v[1];
            if (cnt.count(ratio)) ans += cnt[ratio];
            cnt[ratio] ++;
        }
        return ans;
    }
};