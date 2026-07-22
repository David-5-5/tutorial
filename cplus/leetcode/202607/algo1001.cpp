#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        vector<vector<int>> DIRS = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        set<pair<int, int>> points;
        unordered_map<int, int> rows, cols, diag, anti;
        for (auto& l : lamps) {
            if (!points.count({l[0], l[1]})) {
                points.emplace(l[0], l[1]);
                rows[l[0]] ++; cols[l[1]] ++;
                diag[l[0]-l[1]] ++; anti[l[0]+l[1]] ++;
             }
        }

        int m = queries.size();
        vector<int> ans(m);
        for (int i=0; i<m; i++) {
            auto& r = queries[i][0], c = queries[i][1];
            if (rows[r] || cols[c] || diag[r-c] || anti[r+c]) ans[i] = 1;
            
            for (auto & d : DIRS) {
                auto r_ = r + d[0], c_ = c + d[1];
                if (points.count({r_, c_})) {
                    rows[r_] --; cols[c_] --;
                    diag[r_-c_] --; anti[r_+c_] --;
                    points.erase({r_, c_});
                }
            }
        }
        return ans;
    }
};