#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.3 矩形、多边形
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        // 参考题解 - 枚举对角线
        set<pair<int,int>> hash_points;
        for (auto & p: points) hash_points.insert({p[0], p[1]});
        
        // 枚举对角线
        int n = points.size(), ans = INT_MAX;
        for (int i=0; i<n-1; ++i) for (int j=i+1; j<n; ++j) {
            int x1 = points[i][0], y1 = points[i][1], x2 = points[j][0], y2 = points[j][1];
            if (x1 == x2 || y1 == y2) continue;
            if (hash_points.count({x1, y2}) && hash_points.count({x2, y1})) 
                ans = min(ans, abs(x1-x2)*abs(y1-y2));

        }
        return ans == INT_MAX?0:ans;
    }
};