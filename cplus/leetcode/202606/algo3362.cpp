#include <bits/stdc++.h>
using namespace std;

// 复习
class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
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