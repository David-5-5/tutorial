#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    int orchestraLayout(int num, int xPos, int yPos) {
        // 自行解答，找规律 计算
        int k = min(min(xPos+1, num-xPos), min(yPos+1, num-yPos)) - 1;

        long long inx = 4LL * k * num - 4LL * k * k;        // 外围数量
        int left_x = k, left_y = k, bottom_x = num-1-k, bottom_y = num-1 - k, side= num - 2 * k-1;

        if (xPos == left_x) inx += 1 + yPos - left_y;               // 第一条平行边
        else if (yPos == bottom_y) inx += side + 1 + xPos - left_x; // 第二条垂直边
        else if (xPos == bottom_x) inx += 2LL * side + 1 + bottom_y - yPos; // 第三条平行边
        else inx += 3LL * side + 1 + bottom_x - xPos;               // 第四条垂直边

        return ((inx-1) % 9) + 1;
    }
};