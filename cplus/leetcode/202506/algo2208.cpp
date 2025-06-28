#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    int halveArray(vector<int>& nums) {
        // 自行解答
        priority_queue<double, vector<double>, less<>> pq;

        double sum = 0.0, sub = 0.0;
        for (auto& v : nums) sum += 1.0 * v, pq.push(v);
        sum /= 2;
        int ans = 0;
        while (sub < sum) {
            ans ++;
            double val = pq.top() / 2;
            pq.pop();
            sub += val;
            pq.push(val);
        }

        return ans;  

    }
};