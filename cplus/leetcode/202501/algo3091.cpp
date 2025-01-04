#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 数学贪心 - 基础
class Solution {
public:
    int minOperations(int k) {
        // 自行解答
        int ans = 0, val = 1, cnt = 1;
        while (val * cnt < k) {
            if (cnt < val) cnt ++;
            else val ++;
            ans ++;
        }
        return ans;    
    }
};