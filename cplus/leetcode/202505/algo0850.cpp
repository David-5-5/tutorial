#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.2 二维差分
class Solution {
private:
    // For segment solution
    vector<Node> tree;
    vector<int> hbound;
    
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

struct Node {
    int cover;
    int length;
    int max_length;
};

class Solution {
private:
    // For segment solution
    vector<Node> tree;
    vector<int> x_bound;
    
public:
    void init (int s, int t, int p) {
        tree[p].cover = tree[p].length = 0;
        if (s == t) {
            tree[p].max_length = x_bound[s] - x_bound[s-1];
            return;
        }
        int m = s + ((t - s) >> 1);

        if (s <= m) init(s, m, p*2+1);
        if (t > m) init(m + 1, t, p*2+2);
        tree[p].max_length = tree[p*2+1].max_length + tree[p*2+2].max_length;
    };


    void update (int l, int r, int diff, int s, int t, int p) {
        if (l <= s && t <= r) {
            tree[p].cover += diff;
            maintain(s, t, p);
            return;
        }
        int m = s + ((t - s) >> 1);

        if (l <= m) update(l, r, diff, s, m, p*2+1);
        if (r > m)  update(l, r, diff, m+1, t, p*2+2);
        maintain(s, t, p);
    };

    void maintain(int s, int t, int p) {
        if (tree[p].cover > 0) tree[p].length = tree[p].max_length;
        else if (s == t) tree[p].length = 0;
        else tree[p].length = tree[p*2+1].length + tree[p*2+2].length;
    }

    int rectangleArea(vector<vector<int>>& rectangles) {
        const int mod = 1e9 + 7;
        int n = rectangles.size();
        for (auto& rect : rectangles) {
            x_bound.push_back(rect[1]);     // 上边界 
            x_bound.push_back(rect[3]);     // 下边界
        }
        sort(x_bound.begin(), x_bound.end());
        // unique 将相邻重复元素移动到 vector 末尾，删除重复元素
        x_bound.erase(unique(x_bound.begin(), x_bound.end()), x_bound.end());
        
        // ? 不区分上下边界
        int m = x_bound.size();
        tree.resize(4 * m + 1);
        init(1, m-1, 0);

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
                auto l = lower_bound(x_bound.begin(), x_bound.end(), left) - x_bound.begin() + 1;
                auto r = lower_bound(x_bound.begin(), x_bound.end(), right) - x_bound.begin();
                update(l, r, diff, 1, m-1, 0);
            }
            ans = (ans + 1LL * tree[0].length * (get<0>(sweep[j+1])-get<0>(sweep[j]))) % mod;
            i = j;      // 跳过相同的 x 坐标
        }
    
        return ans;                  
    }
};