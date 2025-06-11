#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        // 自行解答
        priority_queue<tuple<double, int, int>> pq; //  默认是大顶堆
        
        double sum = 0.0;

        for (auto c: classes) {
            int p = c[0], t = c[1];
            if (p == t) sum += 1;
            else {
                sum += 1.0 * p / t;
                pq.emplace(1.0*(p+1)/(t+1) - 1.0*p/t, t, p);
            }
        }

        if (pq.size()) {
            for (int _=0; _<extraStudents; ++_) {
                auto [inc, t, p] = pq.top(); pq.pop();
                sum += inc;
                pq.emplace(1.0*(p+2)/(t+2) - 1.0*(p+1)/(t+1), t+1, p+1);
            }
        }

        return sum / classes.size(); 
    }

};