#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.5 划分型贪心
class Solution {
public:
    int minimumPartition(string s, int k) {
        // 自行解答，尽量增加每一个子数组的长度
        int n = s.length();

        int ans = 0, i = 0;
        while (i < n) {
            long long val = 0;
            while (i < n && val * 10 + s[i]-'0' <= k) {
                val = val * 10 + s[i]-'0'; i++;
            }
            if (val == 0) return -1;
            else {val = 0; ans ++;}
        }
        return ans;   
    }
};