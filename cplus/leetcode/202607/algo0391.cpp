#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        // 参考题解 完美矩阵 除了4个矩阵顶点出现的次数为 1，
        // 其他顶点出现的次数为 2， 4
        // 同时 各个矩阵的面积之和等于完美矩阵的面积
        struct PairHash {
            size_t operator()(const pair<int, int>& p) const {
                // 分别计算两个指针的哈希值
                size_t hash1 = std::hash<int>()(p.first);
                size_t hash2 = std::hash<int>()(p.second);
                
                // 组合两个哈希值（避免碰撞的简单方式）
                return hash1 ^ (hash2 << 1);
            }
        };

        auto mn_x = INT_MAX, mn_y = INT_MAX, mx_a = INT_MIN, mx_b = INT_MIN;
        unordered_map<pair<int,int>, int, PairHash> cnt;
        long long area = 0;
        for (auto r : rectangles) {
            cnt[{r[0],r[1]}] ++; cnt[{r[2],r[3]}] ++;
            cnt[{r[0],r[3]}] ++; cnt[{r[2],r[1]}] ++;
            mn_x = min(mn_x, r[0]); mn_y = min(mn_y, r[1]);
            mx_a = max(mx_a, r[2]); mx_b = max(mx_b, r[3]); 
            area += 1LL * (r[2] - r[0]) * (r[3] - r[1]);
        }   
        // 比较面积
        if (area != 1LL * (mx_a - mn_x) * (mx_b - mn_y)) return false;
        int one = 0;
        for (auto [k, v]: cnt) {
            if (v == 1) {
                one ++; // 数量为 1 顶点为完美矩阵的四个顶点
                if (k.first != mn_x && k.first != mx_a) return false;
                if (k.second != mn_y && k.second != mx_b) return false;
            }
            else if (v != 2 && v != 4) return false;
        }
        return one == 4;
    }
};