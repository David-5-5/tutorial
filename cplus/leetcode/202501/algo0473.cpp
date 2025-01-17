#include <bits/stdc++.h>
using namespace std;

// 类似于 1723，2305
class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        // 方法一 回溯
        int n = matchsticks.size();

        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sum % 4)  return false;
        int limit = sum / 4;

        vector<int> sides(4);
        function<bool(int)>  backtract = [&](int i) ->bool {
            if (i==n)
                return true;

            for (int j=0; j<4; j++) {
                if (sides[j] + matchsticks[i] <= limit) {
                    sides[j] += matchsticks[i];
                    if (backtract(i+1)) {
                        return true;
                    }
                    sides[j] -= matchsticks[i]; // 回溯
                    // 剪枝 -- 关键
                    // 剪枝说明参见 1723 官方题解
                    if (sides[j] == 0 or sides[j] + matchsticks[i] == limit)
                        break;
                }
            }

            return false;
        };

        return backtract(0);
    }
};