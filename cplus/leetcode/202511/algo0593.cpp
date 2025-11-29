#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.3 矩形、多边形
class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // 自行解答 两两相连 6 条边，4条边，2条对角线，对角线是边的sqrt(2)
        vector<vector<int>> points = {p1, p2, p3, p4};
        unordered_map<int, int> side_cnt;

        for (int i=0; i<3; i++) for (int j=i+1; j<4; ++j) {
            int x = points[i][0]-points[j][0], y = points[i][1]-points[j][1];
            side_cnt[x*x + y*y] ++;
        }

        if (side_cnt.size()!= 2) return false;
        int mx_key = 0, mn_key = 0;
        for (auto& k: side_cnt) {
            if (k.first > mx_key) {mn_key = mx_key; mx_key = k.first;}
            else if (k.first > mn_key) mn_key = k.first;
        }

        if (mx_key == 0 || mx_key != 2 * mn_key) return false;
        if (side_cnt[mx_key]!=2 || side_cnt[mn_key]!=4) return false;
        return true;

    }
};