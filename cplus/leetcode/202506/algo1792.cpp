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


    double maxAverageRatio2(vector<vector<int>>& classes, int extraStudents) {
        // 自行解答 - 自定义 cmp 函数
        auto cmp = [](pair<int,int> a, pair<int, int> b) -> bool {
            return 1.0 * (a.second+1)/(a.first+1) - 1.0*a.second/a.first < 
                1.0 * (b.second+1)/(b.first+1) - 1.0*b.second/b.first;
        };
        priority_queue<pair<int, int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp); //  默认是大顶堆
        
        double sum = 0.0;

        for (auto c: classes) {
            int p = c[0], t = c[1];
            if (p == t) sum += 1;
            else {
                sum += 1.0 * p / t;
                pq.emplace(t, p);
            }
        }

        if (pq.size()) {
            for (int _=0; _<extraStudents; ++_) {
                auto [t, p] = pq.top(); pq.pop();
                sum += 1.0*(p+1)/(t+1) - 1.0*p/t;
                pq.emplace(t+1, p+1);
            }
        }

        return sum / classes.size(); 
    }


    double maxAverageRatio3(vector<vector<int>>& classes, int extraStudents) {
        // 自行解答 - 自定义优先队列的结构体 
        struct Ratio {
            int total, pass;
            bool operator < (const Ratio& oth) const {
                return 1.0 * (pass+1)/(total+1) - 1.0*pass/total <
                1.0 * (oth.pass+1)/(oth.total+1) - 1.0*oth.pass/oth.total;
            };
        };
        priority_queue<Ratio> pq; //  默认是大顶堆
        
        double sum = 0.0;

        for (auto c: classes) {
            int p = c[0], t = c[1];
            if (p == t) sum += 1;
            else {
                sum += 1.0 * p / t;
                pq.emplace(t, p);
            }
        }

        if (pq.size()) {
            for (int _=0; _<extraStudents; ++_) {
                auto [t, p] = pq.top(); pq.pop();
                sum += 1.0*(p+1)/(t+1) - 1.0*p/t;
                pq.emplace(t+1, p+1);
            }
        }

        return sum / classes.size(); 
    }
};