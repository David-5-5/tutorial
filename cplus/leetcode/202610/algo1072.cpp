#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        unordered_map<string, int> cnt;
        int m = matrix.size(), n = matrix[0].size();

        for (int i=0; i<m; i++) {
            string key = "0";
            for (int j=1; j<n; j++) {
                if (matrix[i][0] != matrix[i][j]) key += to_string(j);
            }
            cnt[key] += 1;
        } 

        int ans = 0;
        for (auto &[_, v]: cnt) ans = max(ans, v);

        return ans;
    }
};