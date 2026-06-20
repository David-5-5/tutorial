#include <bits/stdc++.h>
using namespace std;

// 贪心 八、其他
class Solution {
public:
    bool robot(string command, vector<vector<int>>& obstacles, int x, int y) {
        // 自行解答
        set<pair<int, int>> coors;

        int t = 0, s = 0;
        for (auto & c: command) {
            coors.emplace(t, s);
            if (c == 'U') s ++;
            else t ++;
        }

        auto t_loops = min(x/t, y/s);
        if (!coors.count({x - t_loops * t, y - t_loops * s})) return false;
        for (auto ob: obstacles) {
            auto u = ob[0], v = ob[1];
            if (u > x || v > y) continue;   // 超出 target 
            auto loops = min(u/t, v/s);
            if (coors.count({u - loops * t, v - loops * s})) return false;            
        }

        return true;
    }
};