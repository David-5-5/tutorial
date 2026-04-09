#include <bits/stdc++.h>
using namespace std;

// LCR series 同会员题 444
class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        // Topological sort
        int n = nums.size();
        
        vector<int> degree(n); vector<set<int>> g(n);
        for (auto & seq : sequences) {
            for (int i=1; i<seq.size(); i++) {
                int u = seq[i-1] - 1, v = seq[i] - 1;
                if (g[u].insert(v).second) degree[v] ++;
            }
        }

        deque<int> q; int inx = 0;
        for (int i=0; i<n; i++) {
            if (degree[i] == 0) q.push_back(i);
        }
        while (!q.empty()) {
            if (q.size() > 1) return false;
            auto u = q.front(); q.pop_front();
            if (nums[inx++] != u+1) return false;
            for (auto v: g[u]) {
                degree[v] --;
                if (degree[v] == 0) q.push_back(v);
            }
        }

        return inx == n;
    }
};