#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        // 自行解答 - 维护大小为 k 的大顶堆
        priority_queue<int, vector<int>, less<>> pq;

        int n = queries.size();
        vector<int> ans(n, -1);
        for (int i=0; i<n; ++i) {
            int x = queries[i][0], y = queries[i][1];
            pq.push(abs(x) + abs(y));
            while (pq.size() > k) pq.pop();

            if (pq.size() == k) ans[i] = pq.top();
        }

        return ans;
    }
};