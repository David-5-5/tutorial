#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.7 最小公倍数
class Solution {
public:
    int mirrorReflection(int p, int q) {
        // 水平方向的速度为 p，竖直方向上速度为 q
        // 到达 0, 1, 2 三个接收点，表示在竖直方向的移动距离 kq 是 p 的整数倍，k 是最小值，
        // 其中 k 的奇偶性决定，在左侧（偶数）还是右侧（奇数）
        //     kq/ p 的奇偶性决定在上侧（奇数）还是下侧（偶数）

        auto l = lcm(p, q); auto k = l/q, kprime = l/p;
        
        if (kprime % 2 == 0) return 0;
        else if (k % 2 == 0) return 2;
        else return 1;
    }
};