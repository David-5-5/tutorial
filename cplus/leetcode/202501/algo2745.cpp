#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 思维题 - 从特殊到一般
class Solution {
public:
    int longestString(int x, int y, int z) {
        // 自行解答
        return (z + min(x,y) * 2 + (y>x|x>y))* 2;
    }
};