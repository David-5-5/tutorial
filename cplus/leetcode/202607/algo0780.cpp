#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        // 逆向思维 类似于辗转相除法
        auto dfs = [&](this auto&& dfs, int x, int y) -> bool {
            if (x == sx && y == sy) return true;
            if (x == sx) return (y - sy) % x == 0;
            if (y == sy) return (x - sx) % y == 0;
            if (x > y) return dfs(x % y, y);
            else return dfs(x, y % x);

        };

        dfs(tx, ty);
    }
};