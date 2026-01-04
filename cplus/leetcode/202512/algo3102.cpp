#include <bits/stdc++.h>
using namespace std;

// 杂项 - 7.3 曼哈顿距离
class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
        // 参考题解，没考虑到预处理，也是 1131 可以优化的地方
        multiset<int> xplusy, xminusy;  // 预处理

        for (auto& p: points) {
            auto & x = p[0], & y = p[1];
            xplusy.emplace(x + y), xminusy.emplace(x - y);
        }

        int ans = INT_MAX;
        for (auto& p: points) {
            auto & x = p[0], & y = p[1];
            xplusy.erase(xplusy.find(x + y)); xminusy.erase(xminusy.find(x - y));
            ans = min(ans, max(*xplusy.rbegin()-*xplusy.begin(), *xminusy.rbegin()-*xminusy.begin()));
            xplusy.emplace(x + y), xminusy.emplace(x - y);
        }

        return ans;

    }

    int minimumDistance2(vector<vector<int>>& points) {
        // 优化，仅删除 xplusy.begin() xplusy.begin() xminusy.begin() xminusy.rbgein
        // first is x + y, x - y, second is index of (x, y) in points
        vector<pair<int, int>> xplusy, xminusy;  // 预处理 
        int n = points.size();
        auto remove = [&](vector<pair<int,int>>& arr, int i) -> int {
            if (arr[0].second == i) 
                return arr[n-1].first - arr[1].first;
            else if (arr[n-1].second == i) 
                return arr[n-2].first - arr[0].first;
            else return arr[n-1].first - arr[0].first;
        };

        for (int i=0; i<n; ++i) {
            auto & x = points[i][0], & y = points[i][1];
            xplusy.emplace_back(x + y, i), xminusy.emplace_back(x - y, i);
        }
        
        sort(xplusy.begin(), xplusy.end()); sort(xminusy.begin(), xminusy.end());
        int ans = INT_MAX;
        int maxValue1 = xplusy[n-1].first - xplusy[0].first;
        int maxValue2 = xminusy[n-1].first - xminusy[0].first;
        if (maxValue1 > maxValue2) {
            int i = xplusy[0].second, j = xplusy.back().second;
            ans = min(ans, max(remove(xplusy, i), remove(xminusy, i)));
            ans = min(ans, max(remove(xplusy, j), remove(xminusy, j)));
        } else {
            int i = xminusy[0].second, j = xminusy.back().second;
            ans = min(ans, max(remove(xplusy, i), remove(xminusy, i)));
            ans = min(ans, max(remove(xplusy, j), remove(xminusy, j)));
        }
        return ans;
    }    
};