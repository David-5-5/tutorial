#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.6 最大公约数（GCD）
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        // 自行解答，暴力求解斜率，都不敢这么做
        int n = points.size(), ans = 0;
        for (int i=0; i<n-1; ++i) {
            // key is slope , value is count of the slope
            // i is the origin
            unordered_map<double, int> k_cnt;
            for (int j=i+1; j<n; ++j) {
                double slope = DBL_MAX;
                if (points[i][0]!=points[j][0]) { // x_i != x_j
                    slope = (1.0 * points[j][1] - points[i][1])/(1.0 * points[j][0] - points[i][0]);
                }
                k_cnt[slope] ++;
                ans = max(ans, k_cnt[slope]);
            }

        }
        return ans+1;
    }

    int maxPoints2(vector<vector<int>>& points) {

        // 模板 计算斜率，按照斜率计数
        struct PairHash {
            size_t operator()(const pair<int, int>& p) const {
                // 分别计算两个指针的哈希值
                size_t hash1 = std::hash<int>()(p.first);
                size_t hash2 = std::hash<int>()(p.second);
                
                // 组合两个哈希值（避免碰撞的简单方式）
                return hash1 ^ (hash2 << 1);
            }
        }; 
        int n = points.size(), ans = 0;
        
        // 归一化斜率
        auto slope = [](int dx, int dy) -> pair<int, int> {
            if (dx == 0) return {1, 0};
            if (dy == 0) return {0, 1};
            int g = gcd(dy, dx);
            auto a = dy/g, b = dx/g;
            if (b < 0) {a = -a; b= - b;}
            return {a, b};
        };

        for (int i=0; i<n-1; ++i) {
            // key is slope , value is count of the slope
            // i is the origin
            unordered_map<pair<int, int>, int, PairHash> k_cnt;
            for (int j=i+1; j<n; ++j) {
                pair<int,int> sl = slope(points[j][0]-points[i][0],  points[j][1] -points[i][1]);
                k_cnt[sl] ++;
                ans = max(ans, k_cnt[sl]);
            }

        }
        return ans+1;        


    }  
};