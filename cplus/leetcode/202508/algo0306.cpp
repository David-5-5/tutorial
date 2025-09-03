#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.3 划分型回溯
class Solution {
public:
    bool isAdditiveNumber(string num) {
        // 自行解答
        const long long MX = 1e17;  // num 长度为 35，MX 的最大十进制位数为 (35-1)/2 = 17

        auto dfs = [&](this auto&& dfs, int i, long long first, long long sec, bool sta) -> bool {
            if (i == num.length()) return sta;
            long long cur = 0;

            for (int j=i; j<num.length(); ++j) {
                cur = cur * 10 + (num[j] - '0');
                if (cur > MX) break;

                if (first == -1) {     
                    if (dfs(j+1, cur, sec, sta)) return true;
                } else if (sec == -1) {
                    if (dfs(j+1, first, cur, sta)) return true;
                } else if (first + sec == cur) {
                    if (dfs(j+1, sec, cur, true)) return true;
                }

                if (cur == 0) break;    // 无前导零
            }
            return false;
        };
        return dfs(0, -1, -1, false);      
    }
}; 