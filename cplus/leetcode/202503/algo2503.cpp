#include <bits/stdc++.h>
using namespace std;

// 周赛 323 复习，练习 c++
class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // union set
        int m = grid.size(), n = grid[0].size();
        int mn = m * n;     // number of elements in grid
        
        vector<int> fa(mn, -1);    // negative imply the count of set
        auto find = [&](this auto&& find, int x) -> int {
            if (fa[x] < 0) return x;

            return fa[x] = find(fa[x]);
        };

        auto merge = [&] (int x, int y) -> int{
            int fx = find(x);
            int fy = find(y);
            if (fx != fy) {
                fa[fy] += fa[fx];
                fa[fx] = y;
            }
            return -fa[fy];
        };
        
        // Sorted element in grid
        array<int, 3> a[mn];
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                a[i*n+j] = {grid[i][j], i, j};
            }
        }
        sort(a, a + mn);

        int k = queries.size(), id[k];
        iota(id, id + k, 0);        // 给容器中元素赋予连续递增的值
        sort(id, id + k, [&](int i, int j) {
            return queries[i] < queries[j];     // id 按照 queries 元素大小排序
        });

        vector<int> ans(k);
        int j = 0; // pointer to array a
        for (int i: id) {
            int q = queries[i];
            for (; j<mn && a[j][0] < q; j++) {
                int x = a[j][1], y = a[j][2];
                for (auto& d : dirs) {
                    int x2 = x + d[0], y2 = y + d[1];
                    if (0 <= x2 && x2 < m && 0 <= y2 && y2 < n && grid[x2][y2] < q) {
                        merge(x * n + y, x2 * n + y2);
                    }
                }
            }
            if (grid[0][0] < q) ans[i] = -fa[find(0)];
        }

        return ans;
    }
};