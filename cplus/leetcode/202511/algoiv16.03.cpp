#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.1 点、线
class Solution {
public:
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        // 自行解答
        int x11 = start1[0], y11 = start1[1], x12 = end1[0], y12 = end1[1];
        int x21 = start2[0], y21 = start2[1], x22 = end2[0], y22 = end2[1];

        // 检查线1和线2是否垂直? 不垂直的线可以继续比较其斜率 k
        bool vert1 = false, vert2 = false;  
        double k1 = 0, b1 = 0, k2 = 0, b2 = 0;

        if (x11 == x12) vert1 = true;
        else {
            k1 = 1.0 * (y11-y12) / (x11-x12);
            b1 = y11 - x11 * k1;
        }

        if (x21 == x22) vert2 = true;
        else {
            k2 = 1.0 * (y21-y22) / (x21-x22);
            b2 = y21 - x21 * k2;
        }
        
        if (vert1 && vert2 ){
            if (x11 == x21)  {
                if (min(y11, y12) > max(y21, y22) || max(y11, y12) < min(y21, y22)) return {};
                else return {1.0*x11, 1.0*max(min(y11, y12), min(y21, y22))};
            }
        } else if (vert1 || vert2) {
            if (vert1) {
                double y = x11 * k2 + b2;
                if (y >= min(y11, y12) && y <= max(y11, y12)) return {1.0*x11, y};
            } else {
                double y = x21 * k1 + b1;
                if (y >= min(y21, y22) && y <= max(y21, y22)) return {1.0*x21, y};
            }
        } else {
            if (k1 == k2) { // b1!=b2 parallel without cross
                if (b1 == b2) {
                    if (!(min(x11, x12) > max(x21, x22) || max(x11, x12) < min(x21, x22))){
                        set<pair<double, double>> points = {{x11,y11},{x12,y12},{x21,y21},{x22,y22}};
                        
                        auto it = points.begin(); it ++;    // The second point
                        return {it->first, it->second};
                    }          
                }
            } else {
                double x = (b2 - b1)/(k1-k2), y = k1 * x + b1;
                if (x>=min(x11,x12) && x<=max(x11,x12) && y>=min(y11,y12) && y<=max(y11,y12) &&
                    x>=min(x21,x22) && x<=max(x21,x22) && y>=min(y21,y22) && y<=max(y21,y22) )
                    return {x,y};
            }
        }
        return {};      
    }
};