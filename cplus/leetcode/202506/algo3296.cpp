#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        // 自行解答，堆，每次找workerTime 最小的工人干活，每工作 1， 工人的workerTime翻倍
        int n = workerTimes.size();

        vector<long> times(n);
        long ans = 0;
        auto cmp = [&](const std::pair<long, int>& a, const std::pair<long, int>& b) {
            return a.first + times[a.second] > b.first + times[b.second];       // 实际上就是下一个最小的值
        };

        priority_queue<pair<long, int>, vector<pair<long, int>>, decltype(cmp)> pq(cmp);
        for (int i=0; i<n; ++i) pq.emplace(workerTimes[i], i);

        while (mountainHeight) {
            mountainHeight --;
            auto [val, inx] = pq.top();
            times[inx] += val;  // 自定义堆排序依赖 times 数组中的值
            pq.pop(); pq.emplace(val+workerTimes[inx], inx);
            ans = max(ans, times[inx]);
        }
        return ans;
    }
};