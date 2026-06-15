#include <bits/stdc++.h>
using namespace std;

// 贪心 八、其他
class Solution {
public:
    bool isRobotBounded(string instructions) {
        vector<pair<int, int>> dirs(4); dirs = {{0, 1}, {-1, 0},{0, -1}, {1, 0}};

        int d = 0, x = 0, y = 0;

        for (auto& ins : instructions) {
            if (ins == 'L') {
                d = (d + 1) % 4;
            } else if (ins == 'R') {
                d = (4 + d - 1) % 4;
            } else {
                x += dirs[d].first, y += dirs[d].second;
            }
        }

        return (x == 0 && y == 0) || d != 0; 
    }
};