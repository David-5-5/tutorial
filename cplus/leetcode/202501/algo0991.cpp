#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 逆向思维
class Solution {
public:
    int brokenCalc(int startValue, int target) {
        // 自行解答，从 target -> startValue 更容易
        int ans = 0;
        while (target > startValue) {
            if (target % 2)  // 更容易判断是否进行 + 操作
                target ++;
            else
                target >>= 1;
            ans += 1;
        }

        return ans + startValue - target;
    }
};