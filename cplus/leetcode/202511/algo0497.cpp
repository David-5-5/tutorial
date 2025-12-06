#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数

// 参考题解
class Solution {
private:
    vector<vector<int>> rects;
    vector<int> pres = {0};
public:
    Solution(vector<vector<int>>& rects) {
        this->rects = rects;
        for (auto rect: rects) {
            auto a = rect[0], b = rect[1], x = rect[2], y = rect[3];
            auto sum = pres.back();
            pres.emplace_back(sum + (x-a+1) * (y-b+1));
        }
    }
    
    vector<int> pick() {
        int k = rand() % pres.back();
        int inx = ranges::upper_bound(pres, k) - pres.begin() - 1;
        k -= pres[inx];
        auto a = rects[inx][0], b = rects[inx][1], y = rects[inx][3];
        auto da = k / (y-b+1), db = k % (y-b+1);
        return {da+a, db+b};

    }
};
