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
        // 自定义 优先队列 的比较函数
        auto cmp = [&](const pair<long, int>& a, const pair<long, int>& b) {
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

    long long minNumberOfSeconds2(int mountainHeight, vector<int>& workerTimes) {
        // 参考题解，简化实现
        int n = workerTimes.size();

        long ans = 0;
        priority_queue<tuple<long, long, int>, vector<tuple<long, long, int>>, greater<>> pq;
        for (auto t: workerTimes) pq.emplace(t, t, t);  // nxt, current, base

        while (mountainHeight) {
            mountainHeight --;
            auto [nxt, cur, base] = pq.top(); pq.pop(); 
            ans = nxt;
            pq.emplace(ans+cur+base, cur+base, base);
        }
        return ans;
    } 

    long long minNumberOfSeconds3(int mountainHeight, vector<int>& workerTimes) {
        // 有单调性，二分答案 n(n-1) = x => n = (1 + sqrt(1+4x)) / 2
        auto check = [&](long mid) -> bool {
            long res = 0;
            for (auto& v:workerTimes) {
                double x =  2.0 * mid / v;
                res += ((int)sqrt(1 + 4.0 * x)-1) / 2;
            }
            return res >= mountainHeight;
        };

        long left = 0, right = (long)ranges::max(workerTimes) * (mountainHeight) * (mountainHeight+1) / 2;

        while (left + 1 < right) {
            long mid = left + (right-left)/2;
            
            (check(mid)? right : left) = mid;
        }

        return right;
    }   
};

int main() {
    vector<int> workTimes = {2,1,1};
    cout << Solution().minNumberOfSeconds3(4, workTimes) << endl;

}