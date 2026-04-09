#include <bits/stdc++.h>
using namespace std;

// 顺序 难度分 3774
class UnionFind {                   // 并查集模板
    vector<int> fa;
public:
    UnionFind(int n): fa(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[max(x,y)] = min(x,y);
        }
    }

    bool is_same(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    bool canReachCorner(int xCorner, int yCorner, vector<vector<int>>& circles) {
        auto check = [](const vector<int>& cir, int s, int t) -> pair<bool,bool> {
            long long cx = cir[0], cy = cir[1], r = cir[2];
            bool first = false;  // x=0 或 y=t -> first = true
            bool second = false; // x=s 或 y=0 -> second = true
            long long r_sq = r * r;

            // ===== 检查 x=0 (左边，y范围 [0, t]) =====
            // 判断区间 [cy - sqrt(K), cy + sqrt(K)] 是否与 [0, t] 相交
            long long dx = abs(cx);
            if (dx <= r) {
                long long K = r_sq - dx * dx;
                bool cond1, cond2;
                // cond1: cy - sqrt(K) <= t  --> 等价于 (cy - t)^2 <= K 当 cy > t
                if (cy <= t) cond1 = true;
                else cond1 = ((cy - t) * (cy - t) <= K);
                // cond2: cy + sqrt(K) >= 0  --> 等价于 (cy)^2 <= K 当 cy < 0
                if (cy >= 0) cond2 = true;
                else cond2 = (cy * cy <= K);
                if (cond1 && cond2) {
                    if (dx == r) {
                        if (cx > 0) first = true; // 相切，圆在右边
                    } else {
                        first = true;
                    }
                }
            }

            // ===== 检查 y=t (上边，x范围 [0, s]) =====
            long long dy = abs(cy - t);
            if (dy <= r) {
                long long K = r_sq - dy * dy;
                bool cond1, cond2;
                if (cx <= s) cond1 = true;
                else cond1 = ((cx - s) * (cx - s) <= K);
                if (cx >= 0) cond2 = true;
                else cond2 = (cx * cx <= K);
                if (cond1 && cond2) {
                    if (dy == r) {
                        if (cy < t) first = true; // 相切，圆在下方
                    } else {
                        first = true;
                    }
                }
            }

            // ===== 检查 x=s (右边，y范围 [0, t]) =====
            long long dx_s = abs(cx - s);
            if (dx_s <= r) {
                long long K = r_sq - dx_s * dx_s;
                bool cond1, cond2;
                if (cy <= t) cond1 = true;
                else cond1 = ((cy - t) * (cy - t) <= K);
                if (cy >= 0) cond2 = true;
                else cond2 = (cy * cy <= K);
                if (cond1 && cond2) {
                    if (dx_s == r) {
                        if (cx < s) second = true; // 相切，圆在左边
                    } else {
                        second = true;
                    }
                }
            }

            // ===== 检查 y=0 (下边，x范围 [0, s]) =====
            long long dy0 = abs(cy);
            if (dy0 <= r) {
                long long K = r_sq - dy0 * dy0;
                bool cond1, cond2;
                if (cx <= s) cond1 = true;
                else cond1 = ((cx - s) * (cx - s) <= K);
                if (cx >= 0) cond2 = true;
                else cond2 = (cx * cx <= K);
                if (cond1 && cond2) {
                    if (dy0 == r) {
                        if (cy > 0) second = true; // 相切，圆在上方
                    } else {
                        second = true;
                    }
                }
            }

            return {first, second};
        };

        auto in_square = [](const vector<int>& cir1, const vector<int>& cir2, int s, int t) -> bool {
            double x1 = cir1[0], y1 = cir1[1], r1 = cir1[2];
            double x2 = cir2[0], y2 = cir2[1], r2 = cir2[2];

            // 计算两圆圆心距离平方
            double dx = x1 - x2;
            double dy = y1 - y2;
            double d_sq = dx * dx + dy * dy;
            double r_sum = r1 + r2;
            double r_diff = r1 - r2;
            double r_sum_sq = r_sum * r_sum;
            double r_diff_sq = r_diff * r_diff;

            // 两圆不相交（内含或相离），无交点，提前返回
            if (d_sq > r_sum_sq + 1e-8 || d_sq < r_diff_sq - 1e-8) {
                return false;
            }

            double d = sqrt(d_sq);
            // 计算交点
            // a = distance from O1 to M (along line O1O2)
            double a = (r1 * r1 - r2 * r2 + d_sq) / (2 * d);
            double h_sq = r1 * r1 - a * a;
            if (h_sq < -1e-8) {
                return false;
            }
            if (h_sq < 0) h_sq = 0;
            double h = sqrt(h_sq);

            // M (midpoint between two intersections)
            // M = O1 + a/d * (O2 - O1)
            // dx = x1 - x2 => O2.x - O1.x = -dx
            // dy = y1 - y2 => O2.y - O1.y = -dy
            double xm = x1 + a * (-dx) / d;
            double ym = y1 + a * (-dy) / d;

            // First intersection point: M + ( -dy*h/d, dx*h/d )
            // because perpendicular direction to (dx, dy) is (-dy, dx)
            double px = xm - dy * h / d;
            double py = ym + dx * h / d;
            if (px > 1e-8 && px < s - 1e-8 && py > 1e-8 && py < t - 1e-8) {
                return true;
            }

            // Second intersection point: M - ( -dy*h/d, dx*h/d )
            if (h > 1e-8) {
                px = xm + dy * h / d;
                py = ym - dx * h / d;
                if (px > 1e-8 && px < s - 1e-8 && py > 1e-8 && py < t - 1e-8) {
                    return true;
                }
            }

            return false;
        };
        int n = circles.size();
        UnionFind uf(n+2);
        for (int i=0; i<n; i++) {
            int xi = circles[i][0], yi = circles[i][1], ri = circles[i][2];
            // if (xi + ri >= xCorner || yi >= yCorner) uf.merge(i, n);
            // if (yi + ri >= yCorner || xi >= xCorner) uf.merge(i, n+1);
            auto res = check(circles[i], xCorner, yCorner);
            // cout << format("first = {} ,second = {}", res.first, res.second );
            if (res.first) uf.merge(i, n);
            if (res.second) uf.merge(i, n+1);

            for (int j=i+1; j<n; j++) {
                int xj = circles[j][0], yj = circles[j][1], rj= circles[j][2];
                // cout <<  in_square(circles[i], circles[j], xCorner, yCorner) << endl;
                if (1LL * (xi-xj)*(xi-xj) + 1LL *(yi-yj)*(yi-yj) <= 1LL * (ri+rj)*(ri+rj) && in_square(circles[i], circles[j], xCorner, yCorner)) {
                    
                 uf.merge(i, j);}
            }
        }

        if (uf.find(n) == uf.find(n+1)) return false;
        else return true;
    }

    bool canReachCorner2(int xCorner, int yCorner, vector<vector<int>>& circles) {      
        // DFS
        auto in_circle = [] (long long ox, long long oy, long long r, long long x, long long y) {
            return (ox - x) * (ox - x) + (oy - y) * (oy - y) <= r * r;
        };

        int n = circles.size();
        vector<int> vis(n);
        auto dfs = [&](auto&& dfs, int i) -> bool {
            long long x1 = circles[i][0], y1 = circles[i][1], r1 = circles[i][2];
            // 圆 i 是否与矩形右边界/下边界相交相切
            if (y1 <= yCorner && abs(x1 - xCorner) <= r1 || x1 <= xCorner && y1 <= r1) {
                return true;
            }
            vis[i] = true;
            for (int j = 0; j < n; j++) {
                long long x2 = circles[j][0], y2 = circles[j][1], r2 = circles[j][2];
                // 在两圆相交相切的前提下，点 A 是否严格在矩形内
                if (!vis[j] && (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2) &&
                    x1 * r2 + x2 * r1 < (r1 + r2) * xCorner &&
                    y1 * r2 + y2 * r1 < (r1 + r2) * yCorner &&
                    dfs(dfs, j)) {
                    return true;
                }
            }
            return false;
        };
        for (int i = 0; i < n; i++) {
            long long x = circles[i][0], y = circles[i][1], r = circles[i][2];
            if (in_circle(x, y, r, 0, 0) || // 圆 i 包含矩形左下角
                in_circle(x, y, r, xCorner, yCorner) || // 圆 i 包含矩形右上角
                // 圆 i 是否与矩形上边界/左边界相交相切
                !vis[i] && (x <= xCorner && abs(y - yCorner) <= r || y <= yCorner && x <= r) && dfs(dfs, i)) {
                return false;
            }
        }
        return true;             
    }


};