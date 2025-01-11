#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 思维题 - 从特殊到一般
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        // 同 2611
        // c++ 排序使用数组中的两个元素相减
        // sort(costs.begin(), costs.end(), 
        //     [](const vector<int>&o1, const vector<int>&o2) {
        //         return (o1[0]-o1[1] < o2[0] - o2[1]);
        //     });
        sort(begin(costs), end(costs), 
            [](const vector<int>&o1, const vector<int>&o2) {
                return (o1[0]-o1[1] < o2[0] - o2[1]);
            });            
        int n = costs.size();
        int ans = 0;
        for (int i = 0; i<n/2; i++) 
            ans += costs[i][0];
        
        for (int i=n/2; i<n; i++)
            ans += costs[i][1];
        
        return ans;
    }
};