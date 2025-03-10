#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 状态机 DP - 进阶
class Solution {
public:
    int largestVariance(string s) {

        int f0 = 1, f1 = INT_MIN;
        int ans = 0;
        for (auto& ch : s) {
            for (int a=0; a<26; a++) {
                for (int b=0; b<26; b++) {
                    if (a == b) continue; // a != b

                    if (ch - 'a' == a) {
                        f0 = max(f0, 0) + 1;
                        f1 ++;
                    } else if (ch - 'a' == b) {
                        v = -1;
                        f1 = f0 = max(f0, 0) - 1;   // 这样看比较清楚，已经减去 -1了，至少包含一个元素
                    }
                    ans = max(ans, f1);
                }
            }
        }

        return ans;
    }


};