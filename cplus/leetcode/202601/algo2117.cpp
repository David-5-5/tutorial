#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    string abbreviateProduct(int left, int right) {
        // 参考题解 统计数字中的 2 及 5
        long double log_ans = 0.0;      // long double 提升精度
        int cnt2 = 0, cnt5 = 0;
        for (int i = left; i <= right; ++i) {
            int x = i;
            while (x % 2 == 0) {
                ++cnt2;
                x /= 2;
            }
            while (x % 5 == 0) {
                ++cnt5;
                x /= 5;
            }
            log_ans += log10(i);
        }
        int cnt0 = min(cnt2, cnt5);
        int k = log_ans;
        if (k + 1 - cnt0 > 10) {
            long double ans_d = log_ans - k;
            // 前 5 个数位
            int first = pow(10, ans_d) * 10000;
            // 后 5 个数位
            int need2 = cnt0, need5 = cnt0;
            int last = 1;
            for (int i = left; i <= right; ++i) {
                int x = i;
                while (need2 && x % 2 == 0) {
                    --need2;
                    x /= 2;
                }
                while (need5 && x % 5 == 0) {
                    --need5;
                    x /= 5;
                }
                last = (long long)last * x % 100000;
            }
            string s_last = to_string(last);
            // 后 5 个数位可能需要在前面补 0
            while (s_last.size() < 5) {
                s_last = '0' + s_last;
            }
            return to_string(first) + "..." + s_last + "e" + to_string(cnt0);
        }
        else {
            int need2 = cnt0, need5 = cnt0;
            long long ans = 1;
            for (int i = left; i <= right; ++i) {
                int x = i;
                while (need2 && x % 2 == 0) {
                    --need2;
                    x /= 2;
                }
                while (need5 && x % 5 == 0) {
                    --need5;
                    x /= 5;
                }
                ans *= x;
            }
            return to_string(ans) + "e" + to_string(cnt0);
        }

    }
};