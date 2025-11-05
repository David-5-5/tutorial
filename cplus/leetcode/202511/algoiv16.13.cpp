#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.1 点、线
class Solution {
public:
    vector<double> cutSquares(vector<int>& square1, vector<int>& square2) {
        // 自行解答，平分两个正方形的直线一定经过正方形的中心
        double x1 = square1[0] + 1.0 * square1[2]/2, y1 = square1[1] + 1.0 * square1[2]/2;
        double x2 = square2[0] + 1.0 * square2[2]/2, y2 = square2[1] + 1.0 * square2[2]/2;

        int x11 = square1[0], x12 = x11 + square1[2], y11 = square1[1], y12 = y11 + square1[2];
        int x21 = square2[0], x22 = x21 + square2[2], y21 = square2[1], y22 = y21 + square2[2];

        if (x1 == x2) { // if y1 == y2, 
            return {x1, 1.0 * min(y11, y21), x2, 1.0 * max(y12, y22)};
        } else if (y1 == y2) {
            return {1.0 * min(x11, x21), y1, 1.0 * max(x12, x22), y2};
        } else {
            double k = 1.0 * (y1-y2) / (x1-x2);
            double b = y1 - x1 * k;

            double y_l = k * min(x11, x21) + b;
            // 判断 x = min(x11, x21) 是否有交点
            bool is_cross = false;
            if ((min(x11,x21) == x11 && y_l >= y11 && y_l <= y12) ||
                (min(x11,x21) == x21 && y_l >= y21 && y_l <= y22))
                is_cross = true;
            
            if (is_cross) {
                return {1.0 * min(x11, x21), y_l, 1.0 * max(x12, x22), k * max(x12, x22) + b};
            } else {
                double x_1 = (min(y11, y21)-b)/k, x_2 = (max(y12,y22)-b)/k;

                if (x_1 <= x_2) return {x_1, 1.0 * min(y11,y21), x_2, 1.0*max(y12,y22)}; 
                else return {x_2, 1.0*max(y12,y22), x_1, 1.0 * min(y11,y21)}; 
            }
        }        
    }
};