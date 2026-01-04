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

};