#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        vector qh(8, vector<bool>(8)); vector<vector<int>> ans;
        for (auto q: queens) qh[q[0]][q[1]] = true;

        auto & kx = king[0], & ky = king[1];
        for (auto & q: queens) {
            auto qx = q[0], qy = q[1]; bool attack = true;
            if (qx == kx) { // 同一行
                while (abs(qy-ky)>1) {
                    qy += qy > ky?-1:1;
                    if (qh[qx][qy]) {
                        attack = false; break;
                    }
                }
            } else if (qy == ky) { // 同一列
                while (abs(qx-kx)>1) {
                    qx += qx > kx?-1:1;
                    if (qh[qx][qy]) {
                        attack = false; break;
                    }
                }
            } else if (qx-qy == kx-ky || qx+qy == kx+ky) {
                while (abs(qx-kx) > 1) {
                    qx += qx > kx?-1:1; qy += qy > ky?-1:1;
                    if (qh[qx][qy]) {
                        attack = false; break;
                    }
                }
            } else attack = false;

            if (attack) ans.push_back(q);
        }
        return ans;
    }
};

