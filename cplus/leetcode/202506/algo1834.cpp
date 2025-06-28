#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        // 自行解答
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        int i = 0, n = tasks.size(), idx[n];
        long cur = 0;
        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return tasks[i] < tasks[j];
        });

        vector<int> ans;
        while (i < n || !pq.empty()) {
            // 设置 cur 的条件
            if (i < n && pq.empty() && cur < tasks[idx[i]][0]) cur = tasks[idx[i]][0];

            while (i<n && tasks[idx[i]][0] <= cur) {
                pq.emplace(tasks[idx[i]][1], idx[i]);
                i++;
            }

            cur += pq.top().first;
            ans.push_back(pq.top().second);
            pq.pop();

        }

        return ans;
    }
};