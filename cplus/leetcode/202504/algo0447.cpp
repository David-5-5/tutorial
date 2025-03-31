#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.2 枚举中间
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        // 参考题解
        unordered_map<int, int> dcnt;
        int n = points.size(), ans = 0;

        for (int i=0; i<n; i++) {       // 遍历 i
            dcnt.clear();
            auto& x1 = points[i][0], y1 = points[i][1];
            // 遍历 j, k 确定 i 的情况下，最后一个是 j，前序的都是 k
            for (int j=0; j!=i && j<n; j++) {
                // 可选，性能反而慢 i = j 时，d = 0
                // 由于 所有点都不相等，d=0仅出现一次，后续不会出现
                // 因此不会记到答案里
                // if (i==j) continue;   
                auto& x2 = points[j][0], y2 = points[j][1];
                int d = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                ans += dcnt[d]++ * 2;   // 先累计答案，在累加
            }
        }

        return ans;
    }
};