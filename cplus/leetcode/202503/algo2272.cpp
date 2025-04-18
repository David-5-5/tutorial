#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 状态机 DP - 进阶
class Solution {
public:
    int largestVariance(string s) {
        // 参考题解 https://leetcode.cn/problems/substring-with-largest-variance/solutions/1494890/by-endlesscheng-5775/
        // 转换为 leetcode 53 最大子数组的和，枚举两个不同的字符a, b，
        // ch = a v = 1, ch = b v = -1, 其他字符 v= = 0 求出子数组的最大和。
        // 定义 f[i+1][0] 表示以 s[i] 结尾的最大子数组和
        // 定义 f[i+1][1] 表示以 s[i] 结尾的，一定包含 b 的最大子数组和
        // 状态转移方程 f[i+1][0] = max(f[i], 0) + v , v=[-1,0,1]
        //            f[i+1][1] = f[i][1] + 1, s[i] == a
        //            f[i+1][1] = f[i][0]    , s[i] == b
        //            f[i+1][1] = f[i][1]    , s[i] != a, b
        // 初始值 f[0][0] = 0, f[0][1] = INT_MIN
        // 代码实现时，f 的第一个维度可以去掉，用两个变量 f0, f1 分别表示 f[i][0] 和 f[i][1]
        int ans = 0;
        for (auto& ch : s) {
            for (int a=0; a<26; a++) {
                int f0 = 1, f1 = INT_MIN;
                for (int b=0; b<26; b++) {
                    if (a == b) continue; // a != b
                    int v = 0;
                    if (ch - 'a' == a) v = 1;
                    else if (ch - 'a' == b) v = -1; // 至少包含一个元素
                    f0 = max(f0, 0) + v;
                    if (ch - 'a' == a) f1 = f1 + 1;
                    else if (ch - 'a' == b) f1 = f0;
                    ans = max(ans, f1);
                }
            }
        }

        return ans;
    }

    int largestVariance2(string s) {
        // 优化 建立 f0[26][26], f1[26][26] 数组
        // 一次遍历 s f0[i][j] i 为出现最多的字母，j 为出现最少的字母
        int f0[26][26]{}, f1[26][26];
        memset(f1, -0x3f, sizeof(f1));  // 初始化

        int ans = 0;
        for (auto& ch : s) {
            int a = ch - 'a';
            for (int b=0; b<26; b++) {
                if (a == b) continue; // a != b

                // a b 假设出现次数最多的字母 a
                f0[a][b] = max(f0[a][b], 0) + 1;
                f1[a][b] ++;
                ans = max(ans, f1[a][b]);
                // b a 假设出现次数最少的字母 a
                f0[b][a] = f1[b][a] = max(f0[b][a], 0) - 1;
                ans = max(ans, f1[b][a]);
            }
        }

        return ans;
    }
};