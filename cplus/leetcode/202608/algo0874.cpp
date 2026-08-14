#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        set<pair<int, int>> ob_set;
        for (auto & ob : obstacles) {
            auto x = ob[0], y = ob[1];
            ob_set.insert({x, y});
        }

        int x = 0, y = 0, d = 0, ans = 0;
        
        for (auto & c : commands) {
            if (c == -2) {
                d = (4 + d - 1) % 4;
            } else if (c == -1) {
                d = (d + 1) % 4;
            } else {
                for (int _=0; _<c; _++) {
                    if (ob_set.count({x+dirs[d][0], y+dirs[d][1]})) {
                        break;
                    }
                    x += dirs[d][0], y += dirs[d][1];
                    ans = max(ans, x * x + y * y);
                }
            }
        }

        return ans;
    }
};