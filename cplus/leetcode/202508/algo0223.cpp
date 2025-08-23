#include <bits/stdc++.h>
using namespace std;

// 
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int areaA = (ax2 - ax1) * (ay2 - ay1);
        int areaB = (bx2 - bx1) * (by2 - by1);

        // 计算重叠部分的宽度和高度
        if (ax2 <= bx1 || ax1 >= bx2 || ay2 <= by1 || ay1 >= by2) {
            return areaA + areaB;
        }else{
            int overlapWidth = min(ax2, bx2) - max(ax1, bx1);
            int overlapHeight = min(ay2, by2) - max(ay1, by1);
            return areaA + areaB - overlapWidth * overlapHeight;
        }

    }

    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        // 这种写法更好理解
        int areaA = (ax2 - ax1) * (ay2 - ay1);
        int areaB = (bx2 - bx1) * (by2 - by1);

        // 计算重叠部分的宽度和高度
        int overlapWidth = min(ax2, bx2) - max(ax1, bx1);
        int overlapHeight = min(ay2, by2) - max(ay1, by1);
        if (overlapWidth > 0 && overlapHeight > 0) {
            return areaA + areaB - overlapWidth * overlapHeight;
        } else {
            return areaA + areaB;
        }

    }
};