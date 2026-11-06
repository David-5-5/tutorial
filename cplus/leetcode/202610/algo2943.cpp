#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        // 找到最大的相邻的 bar 的数量，移除 hBars 和 vBars 最大相邻数量的最小值，就是能得到的最大正方形
        sort(hBars.begin(), hBars.end()); sort(vBars.begin(), vBars.end());

        int h_mx = 1, h_val = 1, v_mx = 1, v_val = 1;
        for (int i=1; i<hBars.size(); i++) {
            if (hBars[i-1] + 1 == hBars[i]) h_val ++;
            else h_val = 1;
            h_mx = max(h_mx, h_val);
        }
        for (int i=1; i<vBars.size(); i++) {
            if (vBars[i-1] + 1 == vBars[i]) v_val ++;
            else v_val = 1;
            v_mx = max(v_mx, v_val);
        }
        auto a = min(h_mx, v_mx) + 1;
        return a * a;      
    }
};