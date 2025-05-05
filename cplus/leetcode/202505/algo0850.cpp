#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.2 二维差分
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        // 参考题解 离散化 + 扫描线 + 数组维护
        const int mod = 1e9 + 7;
        int n = rectangles.size();

        vector<int> y_bound;    // 更直观
        for (auto& rect : rectangles) {
            y_bound.push_back(rect[1]);     // 上边界 
            y_bound.push_back(rect[3]);     // 下边界
        }
        sort(y_bound.begin(), y_bound.end());
        // unique 将相邻重复元素移动到 vector 末尾，删除重复元素
        y_bound.erase(unique(y_bound.begin(), y_bound.end()), y_bound.end());
        
        // ? 不区分上下边界
        int m = y_bound.size();

        vector<int> seg(m - 1);

        vector<tuple<int, int, int>> sweep;     // 扫描线
        for (int i = 0; i < n; ++i) {
            sweep.emplace_back(rectangles[i][0], i, 1); // 左边界
            sweep.emplace_back(rectangles[i][2], i, -1); // 右边界
        }
        sort(sweep.begin(), sweep.end());
        
        long ans = 0;
        for (int i=0; i<sweep.size(); ++i) {
            int j = i;  // j 为 最大的与 i 的 x 坐标相同的
            while (j+1 < sweep.size() && get<0>(sweep[i]) == get<0>(sweep[j + 1]))
                ++j;
            if (j + 1 == sweep.size()) break;

            for (int k=i; k<=j; ++k) {
                auto&& [_, idx, diff] = sweep[k];
                int left = rectangles[idx][1], right = rectangles[idx][3];
                for (int x=0; x<m-1; ++x) {
                    if (left <= y_bound[x] && y_bound[x+1] <= right) seg[x] += diff;
                }
            }
            int cover = 0;
            for (int k=0; k<m-1; ++k) {
                if (seg[k] > 0) cover += (y_bound[k+1]-y_bound[k]);
            }
            ans = (ans + (long)cover * (get<0>(sweep[j+1])-get<0>(sweep[j]))) % mod;
            i = j;      // 跳过相同的 x 坐标
        }
    
        return ans;    
    }
};