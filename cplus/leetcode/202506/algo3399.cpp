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
        // 参考题解 - 最小化最大值 - 二分
        auto check = [&](int m) -> bool {
            int cnt = 0;
            if (m == 1) {   // 需要特判
                // 0110 改成 0101...
                for (int i = 0; i < n; i++) {
                    // 如果 s[i] 和 i 的奇偶性不同，cnt 加一
                    cnt += (s[i] ^ i) & 1;
                }
                // n-cnt 表示改成 1010...
                cnt = min(cnt, n - cnt);    // 取最小值
            } else {
                int k = 0;
                for (int i = 0; i < n; i++) {
                    k++;
                    // 到达连续相同子串的末尾
                    if (i == n - 1 || s[i] != s[i + 1]) {
                        // 对于连续的长度 k 需要分割的次数，
                        // 可以通过举例发现满足规律，符合下式
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

    int minLength2(string s, int numOps) {
        // 参考题解 - 最大堆
        int cnt = 0, n = s.length();
        // 与二分方法相同，仍需要特判最大长度为 1 的情况
        for (int i=0; i<n; ++i) {
            cnt += (s[i] ^ i) & 1;
        }
        if (min(cnt, n-cnt) <= numOps) return 1;

        // 最大堆的元素分别为 子串操作后的(最长子段长度，原始子段长度，段数)
        priority_queue<tuple<int, int, int>> pq;
        int k = 0;
        for (int i=0; i<n; ++i) {
            k++;
            if (i == n-1 || s[i] != s[i+1]) {
                pq.emplace(k,k,1);
                k = 0;
            }
        }
        // 堆顶长度等于 2，即是答案
        // 将原始子串重新分割， floor(k/(seg+1)) k 是原始长度，seg 当前分段数
        while (numOps-- && get<0>(pq.top()) > 2) {
            auto [_, k, seg] = pq.top(); pq.pop();
            pq.emplace(k/(seg+1), k, seg+1); // 重新分割
        }

        return get<0>(pq.top());  
    }

};