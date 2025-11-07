#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 5.2 圆
class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // 参考题解，圆心到正方形最短距离
        long dist = 0;
        if (xCenter < x1 || xCenter > x2)
            dist += min(pow(xCenter-x1, 2), pow(xCenter-x2, 2));
        if (yCenter < y1 || yCenter > y2)
            dist += min(pow(yCenter-y1, 2), pow(yCenter-y2, 2));
        return dist <= radius * radius;   
    }
};