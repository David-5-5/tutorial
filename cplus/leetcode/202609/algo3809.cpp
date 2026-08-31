#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> bestTower(vector<vector<int>>& towers, vector<int>& center, int radius) {
        int mx_q = -1, inx = -1; auto &cx = center[0], &cy = center[1];
        for (int i=0; i<towers.size(); i++) {
            auto & t = towers[i];
            auto & x = t[0], y = t[1], q = t[2];
            if (abs(x-cx) + abs(y-cy) <= radius && q >= mx_q) {
                if (q == mx_q) {
                    if (towers[i][0] <= towers[inx][0] && towers[i][1]<towers[inx][0]) inx = i;
                }else {
                    mx_q = q; inx = i;
                }
            }
        }
        if (inx == -1) return {-1, -1};
        else return {towers[inx][0], towers[inx][1]};
    }
};