#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(string s1, string s2) {
        // 贪心从左开始遍历，保证遍历过后 s1[:i] == s2[:2]（才开始还担心里面有坑）
        if (s1.size() == 1 && s1 != s2 && s1 == "1") return -1;

        int ans = 0, n = s1.length();
        for (int i=0; i<n; i++) {
            if (s1[i] == s2[i]) continue;
            if (s1[i] == '0') {
                ans += 1; // s[i] 0 -> 1
            } else {
                if (i == n-1) ans += 2; // i是最后一位，借前面一位
                else {
                    if (s1[i+1] == '1') {   // 直接将 s1[i, i+1] 设置为 0
                        ans += 1; s1[i+1] = '0';
                    } else { // 先将 s1[i+1]  设为1，再将 s1[i, i+1] 设置为 0
                        ans +=2;
                    }
                }
            }
        }
        return ans;
    }
};