#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.2 堆 - 进阶
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = queries.size(), m = intervals.size(), idx[n], l=0; // l 是 intervals 左指针
        sort(intervals.begin(), intervals.end());

        iota(idx, idx+n, 0);
        sort(idx, idx + n, [&](int i, int j) {
            return queries[i] < queries[j];
        });
        
        // pair<int, int> first:length, second :right
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> ans(n, -1);
        
        for (int i=0; i<n; ++i) {
            int inx = idx[i];
            while (l < m && intervals[l][0] <= queries[inx]) {
                pq.emplace(intervals[l][1]-intervals[l][0] + 1, intervals[l][1]);
                l ++;
            }
            
            while (pq.size() && pq.top().second < queries[inx]) pq.pop();

            if (pq.size()) ans[inx] = pq.top().first;
        }
        return ans;    
    }
};