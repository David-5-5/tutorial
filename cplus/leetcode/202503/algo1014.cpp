#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        // 自行解答
        int prev = values[0], n = values.size(), ans = 0;

        for (int i=1; i<n; i++) {
            ans = max(ans, --prev + values[i]);
            prev = max(prev, values[i]);
        }

        return ans;
    }
};