#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.2 堆 - 进阶
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();

        // 自行解答，有错
        // auto check = [&] (int limit) -> bool {
        //     bool is_chg = false;
        //     int cnt = 1, chg_cnt;
        //     int prev = s[0]-'0';
        //     for (int i=1; i<n; ++i) {
        //         if (prev != s[i]-'0') cnt = 1;
        //         else if (cnt == limit) is_chg = true, cnt = 1;
        //         else cnt ++;
                
        //         prev = s[i]-'0';
        //         if (is_chg) {prev^=1; is_chg=false; chg_cnt++;}
        //         if (chg_cnt>numOps) return false;
        //     }
        //     return true;
        // };
        // 参考题解
        auto check = [&](int m) -> bool {
            int cnt = 0;
            if (m == 1) {
                // 改成 0101...
                for (int i = 0; i < n; i++) {
                    // 如果 s[i] 和 i 的奇偶性不同，cnt 加一
                    cnt += (s[i] ^ i) & 1;
                }
                // n-cnt 表示改成 1010...
                cnt = min(cnt, n - cnt);
            } else {
                int k = 0;
                for (int i = 0; i < n; i++) {
                    k++;
                    // 到达连续相同子串的末尾
                    if (i == n - 1 || s[i] != s[i + 1]) {
                        cnt += k / (m + 1);
                        k = 0;
                    }
                }
            }
            return cnt <= numOps;
        };
                
        int left = 0, right = n+1;
        while (left + 1 < right) {
            int mid = left + (right-left)/2;
            if (check(mid)) right = mid; else left=mid;
        }

        return right;
    }
    
};