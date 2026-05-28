#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int minimumSwap(string s1, string s2) {
        // 分类讨论 和 遍历的区别在于：
        // 分类讨论 统计总体情况(x,y 分别出现的次数），根据总体情况分情况计算结果
        // 遍历    根据每个元素的取值计算结果
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0, n = s1.length();
        for (int i=0; i<n; ++i) if (s1[i] != s2[i]) {
            if (s1[i] == 'x') {
                x1 ++; y2 ++;
            } else {
                y1 ++; x2 ++;
            }
        }
        if ((x1 + x2) % 2 || (y1 + y2) % 2) return -1;

        return x1/2 + y1/2 + (x1%2?2:0);  
    }
};