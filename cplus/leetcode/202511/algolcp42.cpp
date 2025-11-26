#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 计算几何 - 5.2 圆
struct Pair {
    int x;
    vector<int> ys;
};
class Solution {
public:
    int circleGame(vector<vector<int>>& toys, vector<vector<int>>& circles, int r) {
        // 参考题解
        int ans = 0;

        // 1. 对 circles 按 x 升序、x 相同时按 y 升序排序
        sort(circles.begin(), circles.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            }
            return a[1] < b[1];
        });

        // 2. 将横坐标相同的圆分组，同时去重 y 坐标（相同 x 下 y 不重复）
        vector<Pair> a;
        int last_y = -1; // 记录上一个 y，用于去重
        for (const auto& p : circles) {
            int cx = p[0], cy = p[1];
            if (a.empty() || cx > a.back().x) {
                // 新 x 分组：添加新 Pair
                a.push_back({cx, {cy}});
                last_y = cy;
            } else {
                // 同一 x 分组：去重后添加 y
                if (cy > last_y) {
                    a.back().ys.push_back(cy);
                    last_y = cy;
                }
            }
        }

        // 3. 遍历每个玩具，检查是否能被某个圆覆盖
        for (const auto& t : toys) {
            int tx = t[0], ty = t[1], tr = t[2];
            // 玩具半径大于圆半径，直接跳过
            if (tr > r) {
                continue;
            }
            int max_dist_sq = (r - tr) * (r - tr); // 允许的最大距离平方（避免开方，提高效率）

            // 二分查找第一个满足：a[i].x + r >= tx + tr 的分组（x 方向左边界）
            int i = lower_bound(a.begin(), a.end(), tx + tr, [&](const Pair& p, int target) {
                return p.x + r < target;
            }) - a.begin();

            // 遍历符合 x 范围的分组：a[i].x - r <= tx - tr（x 方向右边界）
            for (; i < a.size() && (a[i].x - r) <= (tx - tr); ++i) {
                int cx = a[i].x;
                const vector<int>& ys = a[i].ys;

                // 二分查找 ys 中第一个 >= ty 的元素索引
                auto j_it = lower_bound(ys.begin(), ys.end(), ty);
                int j = j_it - ys.begin();

                // 检查当前索引 j 的 y（ys[j] 是 >= ty 的最小 y）
                if (j < ys.size()) {
                    int cy = ys[j];
                    long long dist_sq = (long long)(tx - cx) * (tx - cx) + (long long)(ty - cy) * (ty - cy);
                    if (dist_sq <= (long long)max_dist_sq) {
                        ans++;
                        break; // 找到一个圆即可，跳过后续检查
                    }
                }

                // 检查前一个索引 j-1 的 y（ys[j-1] 是 <= ty 的最大 y）
                if (j > 0) {
                    int cy = ys[j-1];
                    long long dist_sq = (long long)(tx - cx) * (tx - cx) + (long long)(ty - cy) * (ty - cy);
                    if (dist_sq <= (long long)max_dist_sq) {
                        ans++;
                        break; // 找到一个圆即可，跳过后续检查
                    }
                }
            }
        }

        return ans;
    }
};