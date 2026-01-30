#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.2 全源最短路：Floyd 算法
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        // Floyd
        vector f(numCourses, vector<bool>(numCourses));

        for (auto p : prerequisites) {
            f[p[0]][p[1]] = true;
        }

        for (int k=0; k<numCourses; k++) for (int i=0; i<numCourses; i++) for (int j=0; j<numCourses; j++) {
            f[i][j] = f[i][j] || (f[i][k] && f[k][j]);
        }

        vector<bool> ans;
        for (auto& q: queries) ans.push_back(f[q[0]][q[1]]);

        return ans;

    }
};