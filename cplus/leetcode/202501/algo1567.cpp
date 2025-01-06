#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 数学贪心 - 乘积贪心
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        // 自行解答 贪心
        int first = -1, second = -1;
        int cur = 0, ans = 0, cnt = 0;

        for (int i=0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                first = second = -1;
                cnt = cur = 0;
            } else if (nums[i] < 0) {
                cnt = (cnt + 1) % 2;
                if (cnt == 1) {
                    if (first == -1) first = i-cur;
                    if (second != -1) cur = i - second + 1;
                    else cur = 0;
                } else {
                    if (second == -1) second = i-cur;
                    cur = i - first + 1;
                }

            } else cur += 1;
            ans = max(cur, ans);
        }

        return ans;  

    }
};