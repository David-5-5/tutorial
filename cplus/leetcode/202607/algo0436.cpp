#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<pair<int, int>> start, end;
        for (int i=0; i<n; i++) {
            auto x = intervals[i];
            start.emplace_back(x[0], i);
            end.emplace_back(x[1], i);
        }
        sort(start.begin(), start.end()); sort(end.begin(), end.end()); 

        vector<int> ans(n, -1);
        for (int i=0, j = 0; i<n && j<n; i++) {
            while (j<n && start[j] < end[i]) j++;
            if (j<n) ans[end[i].second] = start[j].second;
        }

        return ans;
    }
};