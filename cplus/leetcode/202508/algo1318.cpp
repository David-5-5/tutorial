#include <bits/stdc++.h>
using namespace std;

// 位运算 - 与或（AND/OR）的性质
class Solution {
public:
    int minFlips(int a, int b, int c) {
        // 自行解答，操作符的优先级，加括号很重要
        int ans = 0;
        while (a || b || c) {
            if (((a&1) | (b&1)) != (c&1)){
                if (c&1 == 1) ans += 1;
                else {ans += a&1; ans += b&1;};
            }
            a >>= 1, b >>= 1, c >>= 1;
        }
        
        return ans;
    }
};