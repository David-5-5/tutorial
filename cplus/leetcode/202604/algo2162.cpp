#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {
        int ans = INT_MAX;
        int m_max = min(targetSeconds / 60, 99), m_min = (targetSeconds - 99 + 59) / 60;
        
        for (int mm =m_min; mm <=m_max; mm++) {
            auto ss = targetSeconds - 60 * mm;
            int res = 0;
            if (mm == 0) {
                if (ss < 10) res = pushCost + ((ss == startAt)?0:moveCost);
                else res = 2 * pushCost  + ((ss/10 == startAt)?0:moveCost)
                    + ((ss/10 == ss%10)?0:moveCost); // ss 秒的两位不同需要移位
            } else {
                if (mm < 10) res = 3 * pushCost + ((mm == startAt)?0:moveCost) 
                        + ((mm == ss/10)?0:moveCost)    // 分钟末位和秒首位不同，需要移位
                        + ((ss/10 == ss%10)?0:moveCost) ; // ss 秒的两位不同需要移位
                else res = 4 * pushCost + ((mm/10 == startAt)?0:moveCost) 
                        + ((mm/10 == mm%10)?0:moveCost)   // 分钟的两位不同需要移位
                        + ((mm%10 == ss/10)?0:moveCost)   // 分钟末位和秒首位不同，需要移位
                        + ((ss/10 == ss%10)?0:moveCost) ; // ss 秒的两位不同需要移位
            }

            ans = min(ans, res);
        }

        return ans;

    }
};