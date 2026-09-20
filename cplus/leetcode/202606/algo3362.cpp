#include <bits/stdc++.h>
using namespace std;

// 复习
class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        // Greedy: sort queries by left endpoint, use max‑heap to select the farthest right endpoint
        // when current position lacks required deletions; difference array maintains range add,
        // leftover queries inside heap are the maximum removable count, return‑1 if impossible.
        priority_queue<int> pq;

        int n = nums.size(), m = queries.size(), sum = 0, j = 0;
        vector<int> diff(n);
        sort(queries.begin(), queries.end());

        for (int i=0; i<n; i++) {
            while (j < m && queries[j][0] <= i) {
                pq.emplace(queries[j][1]); j ++;
            }
            sum += diff[i];
            while (sum < nums[i]) {
                if (pq.size() == 0 || pq.top() < i) return -1;
                if (pq.top()+1 < n) diff[pq.top()+1] --; 
                sum ++; pq.pop();
            }
        }
        
        return pq.size();
    }
};